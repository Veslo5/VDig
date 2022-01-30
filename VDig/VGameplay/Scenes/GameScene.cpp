#include "GameScene.h"

#include "../../Vengine/VGame.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

bool startedPainting = false;

Vgameplay::GameScene::GameScene(std::string name, Vengine::VGame* game) : Scene(name, game),
MyGridWorld(32, 32, 50, 0),
RenderTexture(32 * 50, 32 * 50),
AtlasTest("res/atlas.png",16,10),
AnimTest("res/anim.png",4,1,0.5f)
{
	
}

Vgameplay::GameScene::~GameScene() = default;

void Vgameplay::GameScene::LoadContent()
{
	RenderTexture.BeginMode();
	ClearBackground(raylib::Color::Black());
	RenderTexture.EndMode();
}	

void Vgameplay::GameScene::UnloadContent()
{

}

void Vgameplay::GameScene::Update(float deltaTime)
{
	if (IsKeyDown(KEY_W)) {
		this->Game->Camera.target.y -= deltaTime * 200;
	}
	if (IsKeyDown(KEY_S)) {
		this->Game->Camera.target.y += deltaTime * 200;
	}
	if (IsKeyDown(KEY_A)) {
		this->Game->Camera.target.x -= deltaTime * 200;
	}
	if (IsKeyDown(KEY_D)) {
		this->Game->Camera.target.x += deltaTime * 200;
	}

	AnimTest.Update(deltaTime);

	RenderTexture.BeginMode();

	if (startedPainting == false)
	{
		for (const auto& element : MyGridWorld.TileWorld)
		{
			Red.DrawRectangleLines(element->Position.x, element->Position.y, element->Size, element->Size);
		}

		startedPainting = true;
	}

	RenderTexture.EndMode();
}

void Vgameplay::GameScene::CameraDraw()
{
	DrawTexture(RenderTexture.texture, 0, 0, raylib::Color::White());

}

void Vgameplay::GameScene::Draw()
{
	DrawFPS(0, 0);
	//AnimTest.Draw(AnimTest.AtlasPositions[AnimTest.CurrentFrame],  raylib::Vector2(64, 80));
	AnimTest.Draw(AnimTest.AtlasPositions[AnimTest.CurrentFrame], raylib::Rectangle(64,80,100,100));
	AtlasTest.Draw(AtlasTest.AtlasPositions[0], raylib::Vector2(8, 80));
	AtlasTest.Draw(AtlasTest.AtlasPositions[1], raylib::Vector2(16, 80));
	AtlasTest.Draw(AtlasTest.AtlasPositions[2], raylib::Vector2(24, 80));
	AtlasTest.Draw(AtlasTest.AtlasPositions[3], raylib::Vector2(32, 80));
	AtlasTest.Draw(AtlasTest.AtlasPositions[4], raylib::Vector2(40, 80));
	AtlasTest.Draw(AtlasTest.AtlasPositions[5], raylib::Vector2(48, 80));
}

