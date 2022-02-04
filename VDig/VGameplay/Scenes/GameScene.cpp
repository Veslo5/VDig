#include "GameScene.h"

#include "../../Vengine/VGame.h"
#include "MenuScene.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Vgameplay::GameScene::GameScene(std::string name, Vengine::VGame* game) : VScene(name, game),
MyGridWorld(16, 16, 50, 0)
{

}


void Vgameplay::GameScene::LoadContent()
{
	this->Camera.SetTarget(raylib::Vector2(0, 0));

	this->Game->DataManager.TextureHolder.AddToLoadingQueue("res/atlas.png");
	this->Game->DataManager.TextureHolder.AddToLoadingQueue("res/anim.png");
	this->Game->DataManager.LoadAll();

	AtlasTest = std::make_unique<Vengine::VAtlas>(this->Game->DataManager.TextureHolder.GetTexture("res/atlas.png"));
	AnimTest = std::make_unique<Vengine::VAnimation>(this->Game->DataManager.TextureHolder.GetTexture("res/anim.png"));
	RenderTexture = std::make_unique<raylib::RenderTexture>(16 * 50, 16 * 50);

	AtlasTest->CalculatePositions(16, 10);
	AnimTest->CalculatePositions(4, 1);

}

void Vgameplay::GameScene::UnloadContent()
{
	this->Game->DataManager.UnloadAll();
}

void Vgameplay::GameScene::Update(float deltaTime)
{
	this->Camera.SetZoom(this->Game->WindowWidth / 1366.f);
	this->Camera.SetOffset(raylib::Vector2(this->Game->WindowWidth / 2, this->Game->WindowHeight / 2));


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

	AnimTest->Update(deltaTime);


}

void Vgameplay::GameScene::Draw()
{
	if (startedPainting == false)
	{
		RenderTexture->BeginMode();
		{
			ClearBackground(raylib::Color::Black());


			for (const auto& element : MyGridWorld.TileWorld)
			{
				Red.DrawRectangleLines(element->Position.x, element->Position.y, element->Size, element->Size);
			}

		}
		RenderTexture->EndMode();
		startedPainting = true;
	}

	BeginDrawing();
	{
		Game->ClearBackground();

		Camera.BeginMode();
		DrawTexture(RenderTexture->texture, 0, 0, raylib::Color::White());
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

