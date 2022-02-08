#include "GameScene.h"
#include "VGame.h"
#include "MenuScene.h"
#include "FastNoiseLite.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

raylib::Vector2 pos1 = { 0,0 };
raylib::Vector2 pos2 = { 0,0 };
bool firstSet = false;

Vgameplay::GameScene::GameScene(std::string name, Vengine::VGame* game) : VScene(name, game),
MyGridWorld(128, 128, 8, 0)
{

}


void Vgameplay::GameScene::LoadContent()
{
	this->Camera.SetTarget(raylib::Vector2(0, 0));

	this->Game->DataManager.TextureHolder.AddToLoadingQueue("res/atlas.png");
	this->Game->DataManager.TextureHolder.AddToLoadingQueue("res/anim.png");
	this->Game->DataManager.TextureHolder.AddToLoadingQueue("res/tileset.png");
	this->Game->DataManager.LoadAll();

	AtlasTest = std::make_unique<Vengine::VAtlas>(this->Game->DataManager.TextureHolder.GetTexture("res/atlas.png"));
	AnimTest = std::make_unique<Vengine::VAnimation>(this->Game->DataManager.TextureHolder.GetTexture("res/anim.png"));
	GameTileSet = std::make_unique<Vengine::VAtlas>(this->Game->DataManager.TextureHolder.GetTexture("res/tileset.png"));

	RenderTexture = std::make_unique<raylib::RenderTexture>(128 * 8, 128 * 8);
	PathFinder.setWorldSize({ 128,128 });
	PathFinder.setHeuristic(AStar::Heuristic::euclidean);
	PathFinder.setDiagonalMovement(false);

	AtlasTest->CalculatePositions(16, 10);
	AnimTest->CalculatePositions(4, 1);
	GameTileSet->CalculatePositions(23, 21);

	this->generateGrid();

}

void Vgameplay::GameScene::UnloadContent()
{
	this->Game->DataManager.UnloadAll();
}

void Vgameplay::GameScene::Update(float deltaTime)
{
	this->Camera.SetZoom((this->Game->WindowWidth / 1366.f) + cameraZoom);
	this->Camera.SetOffset(raylib::Vector2(this->Game->WindowWidth / 2, this->Game->WindowHeight / 2));


	if (IsMouseButtonPressed(0))
	{
		auto pos = GetScreenToWorld2D(GetMousePosition(), Camera);
		auto tile = MyGridWorld.GetTileAtWorldPos(pos.x, pos.y);

		if (!tile.expired())
		{
			if (auto lockedTile = tile.lock())
			{
				lockedTile->AtlasPosition = 0;
				startedPainting = false;
			}
		}


	}


	if (IsMouseButtonPressed(1))
	{

		auto pos = GetScreenToWorld2D(GetMousePosition(), Camera);
		auto tile = MyGridWorld.GetTileAtWorldPos(pos.x, pos.y);

		if (!tile.expired())
		{
			if (firstSet == false)
			{
				if (auto lockedTile = tile.lock())
				{
					pos1 = lockedTile->GridPosition;
				}
				firstSet = true;
			}else
			{
				if (auto lockedTile = tile.lock())
				{
					pos2 = lockedTile->GridPosition;
				}
				firstSet = false;

				task = std::async(std::launch::async, &GameScene::loadPath, this);
				
			}

		}
	}



	if (IsKeyPressed(KEY_SPACE))
	{
		this->Game->SceneManager.ChangeScene<MenuScene>("MenuScene");
	}

	if (IsKeyDown(KEY_W)) {
		this->Camera.target.y -= deltaTime * 200;
	}
	if (IsKeyDown(KEY_S)) {
		this->Camera.target.y += deltaTime * 200;
	}
	if (IsKeyDown(KEY_A)) {
		this->Camera.target.x -= deltaTime * 200;
	}
	if (IsKeyDown(KEY_D)) {
		this->Camera.target.x += deltaTime * 200;
	}
	if (IsKeyDown(KEY_Q)) {
		this->cameraZoom += deltaTime;
	}
	if (IsKeyDown(KEY_E)) {
		this->cameraZoom -= deltaTime;
	}
	if (IsKeyPressed(KEY_R))
	{
		this->generateGrid();
	}

	AnimTest->Update(deltaTime);


}

void Vgameplay::GameScene::Draw()
{
	if (startedPainting == false)
	{
		RenderTexture->BeginMode();
		{
			ClearBackground(raylib::Color::Black());


			for (const std::shared_ptr<Tile>& element : MyGridWorld.TileWorld)
			{

				GameTileSet->Draw(element->AtlasPosition, element->WorldPosition);
				//element->Color.DrawRectangleLines(element->Position.x, element->Position.y, element->Size, element->Size);
			}

		}
		RenderTexture->EndMode();
		startedPainting = true;
	}

	BeginDrawing();
	{
		Game->ClearBackground();

		Camera.BeginMode();
		DrawTextureRec(RenderTexture->texture, raylib::Rectangle(0, 0, RenderTexture->texture.width, -RenderTexture->texture.height), raylib::Vector2(0, 0), raylib::Color::White());
		Camera.EndMode();


		DrawFPS(0, 0);


		//AnimTest.Draw(AnimTest.AtlasPositions[AnimTest.CurrentFrame],  raylib::Vector2(64, 80));
		AnimTest->Draw(raylib::Rectangle(64, 80, 100, 100));
		AtlasTest->Draw(0, raylib::Vector2(8, 80));
		AtlasTest->Draw(1, raylib::Vector2(16, 80));
		AtlasTest->Draw(2, raylib::Vector2(24, 80));
		AtlasTest->Draw(3, raylib::Vector2(32, 80));
		AtlasTest->Draw(4, raylib::Vector2(40, 80));
		AtlasTest->Draw(5, raylib::Vector2(48, 80));

	}
	EndDrawing();

}

void Vgameplay::GameScene::generateGrid()
{
	int seed = GetRandomValue(0, 999999999);

	FastNoiseLite noiseTrees;
	noiseTrees.SetSeed(seed);
	noiseTrees.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noiseTrees.SetFrequency(0.100f);
	noiseTrees.SetFractalType(FastNoiseLite::FractalType_Ridged);
	noiseTrees.SetFractalOctaves(1);
	noiseTrees.SetFractalLacunarity(2);
	noiseTrees.SetFractalGain(0.50f);

	FastNoiseLite noiseGold;
	noiseGold.SetSeed(seed);
	noiseGold.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noiseGold.SetFractalType(FastNoiseLite::FractalType_FBm);
	noiseGold.SetFractalOctaves(5);
	noiseGold.SetFractalLacunarity(2.8f);
	noiseGold.SetFractalGain(2);
	noiseGold.SetFractalWeightedStrength(1);


	for (const std::shared_ptr<Tile>& tile_world : MyGridWorld.TileWorld)
	{
		tile_world->AtlasPosition = 0;

		//# WALLS
		if (tile_world->GridPosition.x == 0)
		{
			tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(0, 15);
		}

		if (tile_world->GridPosition.y == 0)
		{
			tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(3, 15);
		}

		if (tile_world->GridPosition.x == MyGridWorld.Width - 1)
		{
			tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(5, 15);
		}

		if (tile_world->GridPosition.y == MyGridWorld.Height - 1)
		{
			tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(3, 15);
		}
		//# END WALLS

		const float treeF = noiseTrees.GetNoise(tile_world->GridPosition.x, tile_world->GridPosition.y);

		if (treeF < 0.1f)
		{
			//tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(9, 11);
			PathFinder.addCollision({ static_cast<int>(tile_world->GridPosition.x) , static_cast<int>(tile_world->GridPosition.y) });
			tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(8, 11);
		}
		else if (treeF < 0.5f && treeF > 0.1f)
		{
		}
		else
		{
		}
		const float goldF = noiseGold.GetNoise(tile_world->GridPosition.x, tile_world->GridPosition.y);


		if (goldF > 0.1f)
		{
			tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(22, 3);
		}

	}

	startedPainting = false;
}

void Vgameplay::GameScene::loadPath()
{
	auto path = PathFinder.findPath({ static_cast<int>(pos1.x), static_cast<int>(pos1.y) }, { static_cast<int>(pos2.x), static_cast<int>(pos2.y) });

	for (auto& vec2_i : path)
	{
		auto tile = MyGridWorld.GetTileAtPos(vec2_i.x, vec2_i.y);
		if (auto lockedTile = tile.lock())
		{
			lockedTile->AtlasPosition = GameTileSet->GetIndexFromPosition(14, 1);
		}
	}
	startedPainting = false;

}

