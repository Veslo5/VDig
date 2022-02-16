#include "GameScene.h"
#include "VGame.h"
#include "MenuScene.h"
#include "FastNoiseLite.h"
#include "../TileBuilder.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Vgameplay::TileBuilder builder;
bool JoinRoads;

Vgameplay::GameScene::GameScene(std::string name, Vengine::VGame* game) : VScene(name, game),
MyGridWorld(32, 32, 8, 0)
{

}


void Vgameplay::GameScene::LoadContent()
{
	this->Camera.SetTarget(raylib::Vector2(0, 0));

	this->Game->DataManager.TextureHolder.AddToLoadingQueue("res/tileset.png");
	this->Game->DataManager.LoadAll();

	GameTileSet = std::make_unique<Vengine::VAtlas>(this->Game->DataManager.TextureHolder.GetTexture("res/tileset.png"));

	RenderTexture = std::make_unique<raylib::RenderTexture>(MyGridWorld.GetPixelSizeX(), MyGridWorld.GetPixelSizeY());

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

		auto gridPos = MyGridWorld.GetGridPositionFromWorldPosition(pos);
		auto selectedTiles = MyGridWorld.GetSurroundingTilesFromGridPosition(gridPos);

		auto atlasPosition = builder.CalculateAtlasIndexForTiling(GameTileSet.get(), selectedTiles);

		if (selectedTiles.CenterTile)
		{
			selectedTiles.CenterTile->AtlasPosition = atlasPosition;
			selectedTiles.CenterTile->Type = TileType::path;
		}


		if (selectedTiles.NorthTile && selectedTiles.NorthTile->Type == TileType::path)
		{
			auto selectedTilesSecond = MyGridWorld.GetSurroundingTilesFromGridPosition(selectedTiles.NorthTile->GridPosition);
			auto atlasPosition2 = builder.CalculateAtlasIndexForTiling(GameTileSet.get(), selectedTilesSecond);


			selectedTilesSecond.CenterTile->AtlasPosition = atlasPosition2;
			selectedTilesSecond.CenterTile->Type = TileType::path;
		}

		if (selectedTiles.EastTile && selectedTiles.EastTile->Type == TileType::path)
		{
			auto selectedTilesSecond = MyGridWorld.GetSurroundingTilesFromGridPosition(selectedTiles.EastTile->GridPosition);
			auto atlasPosition2 = builder.CalculateAtlasIndexForTiling(GameTileSet.get(), selectedTilesSecond);


			selectedTilesSecond.CenterTile->AtlasPosition = atlasPosition2;
			selectedTilesSecond.CenterTile->Type = TileType::path;
		}

		if (selectedTiles.SouthTile && selectedTiles.SouthTile->Type == TileType::path)
		{
			auto selectedTilesSecond = MyGridWorld.GetSurroundingTilesFromGridPosition(selectedTiles.SouthTile->GridPosition);
			auto atlasPosition2 = builder.CalculateAtlasIndexForTiling(GameTileSet.get(), selectedTilesSecond);


			selectedTilesSecond.CenterTile->AtlasPosition = atlasPosition2;
			selectedTilesSecond.CenterTile->Type = TileType::path;
		}

		if (selectedTiles.WestTile && selectedTiles.WestTile->Type == TileType::path)
		{
			auto selectedTilesSecond = MyGridWorld.GetSurroundingTilesFromGridPosition(selectedTiles.WestTile->GridPosition);
			auto atlasPosition2 = builder.CalculateAtlasIndexForTiling(GameTileSet.get(), selectedTilesSecond);


			selectedTilesSecond.CenterTile->AtlasPosition = atlasPosition2;
			selectedTilesSecond.CenterTile->Type = TileType::path;
		}




		startedPainting = false;
	}

	//	surrounding_tile->AtlasPosition = = GameTileSet->GetIndexFromPosition(15,1);;
	//	startedPainting = false;

	/*if (MyGridWorld.SetTileDataWorldPos(pos.x, pos.y, 0))
	{
		startedPainting = false;
	}*/



	if (IsMouseButtonDown(0))
	{
		auto pos = GetScreenToWorld2D(GetMousePosition(), Camera);
		builder.CalculateTiles(MyGridWorld.GetGridPositionFromWorldPosition(pos), GameTileSet.get());
	}

	if (IsMouseButtonReleased(0))
	{
		builder.EndCalculation();
	}


	if (IsMouseButtonPressed(1))
	{
		auto pos = GetScreenToWorld2D(GetMousePosition(), Camera);
		auto* tile = MyGridWorld.GetTileAtWorldPos(pos);

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
}

void Vgameplay::GameScene::Draw()
{
	if (startedPainting == false)
	{
		RenderTexture->BeginMode();
		{
			ClearBackground(Game->ClearColor);

			for (const std::unique_ptr<Tile>& element : MyGridWorld.TileWorld)
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
		DrawTextureRec(RenderTexture->texture, raylib::Rectangle(0, 0, static_cast<float>(RenderTexture->texture.width), static_cast<float>(-RenderTexture->texture.height)), raylib::Vector2(0, 0), raylib::Color::White());
		//GameTileSet->Draw(GameTileSet->GetIndexFromPosition(9, 13), MyGridWorld.GetVectorAlignedToGrid(Camera.GetScreenToWorld(GetMousePosition())), raylib::Color(255, 255, 255, 127));
		for (const auto& selected_tile : builder.SelectedTiles)
		{
			GameTileSet->Draw(selected_tile.AtlasPosition, MyGridWorld.GetWorldPositionFromGridPosition(selected_tile.GridPosition));
		}

		Camera.EndMode();


		JoinRoads = GuiCheckBox(raylib::Rectangle(10, 100, 20, 20), "JoinRoads", JoinRoads);

		DrawFPS(0, 0);

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


	for (const std::unique_ptr<Tile>& tile_world : MyGridWorld.TileWorld)
	{
		tile_world->AtlasPosition = 0;


		const float treeF = noiseTrees.GetNoise(static_cast<float>(tile_world->GridPosition.x), static_cast<float>(tile_world->GridPosition.y));

		if (treeF < 0.1f)
		{
			//tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(9, 11);
			tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(8, 11);
		}
		else if (treeF < 0.5f && treeF > 0.1f)
		{
		}
		else
		{
		}
		const float goldF = noiseGold.GetNoise(static_cast<float>(tile_world->GridPosition.x), static_cast<float>(tile_world->GridPosition.y));


		if (goldF > 0.1f)
		{
			tile_world->AtlasPosition = GameTileSet->GetIndexFromPosition(22, 3);
		}

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

	}

	startedPainting = false;
}




