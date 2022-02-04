#include "BoxScene.h"
#include  "raylib-cpp.hpp"
#include  "b2_math.h"
#include  "b2_world.h"
#include "b2_body.h"
#include "../../Vengine/VGame.h"


Vgameplay::BoxScene::BoxScene(std::string name, Vengine::VGame* game) : VScene(name, game)
{

}

Vgameplay::BoxScene::~BoxScene() = default;



void Vgameplay::BoxScene::UnloadContent()
{
}

void Vgameplay::BoxScene::LoadContent()
{
}

void Vgameplay::BoxScene::Update(float deltaTime)
{
}

void Vgameplay::BoxScene::Draw()
{
	BeginDrawing();
	this->Game->ClearBackground();

	raylib::Color::White().DrawRectangle(100, 100, 100, 100);
	EndDrawing();
}
