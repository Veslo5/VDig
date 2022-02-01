
#include "MenuScene.h"
#include "raylib-cpp.hpp"
#include "../../Vengine/VGame.h"
#include "GameScene.h"
#include <iostream>
#include <memory>


	Vgameplay::MenuScene::MenuScene(std::string name, Vengine::VGame* game) : VScene(name, game), white(raylib::Color::White())
	{
	}

	Vgameplay::MenuScene::~MenuScene() = default;

	void Vgameplay::MenuScene::LoadContent()
	{
		this->Game->Camera.SetTarget(raylib::Vector2(0, 0));
		this->Game->Camera.SetOffset(raylib::Vector2(this->Game->WindowWidth / 2, this->Game->WindowHeight / 2));
		this->Game->Camera.SetZoom(1.0f);
		sprite = std::make_unique<raylib::Texture2D>("res/test.png");
	}

	void Vgameplay::MenuScene::UnloadContent()
	{
	}

	void Vgameplay::MenuScene::Update(float deltaTime)
	{		
		if (IsKeyPressed(KEY_SPACE))
		{
			this->Game->SceneManager.ChangeScene<GameScene>("GameScene");
		}

		/*if (IsKeyPressed(KEY_RIGHT_ALT))
		{
			this->Game->SceneManager.ChangeScene<BoxScene>("BoxScene");
		}*/

		if (IsKeyDown(KEY_W)) {
			this->Game->Camera.zoom += deltaTime;
		}
		if (IsKeyDown(KEY_S)) {
			this->Game->Camera.zoom -= deltaTime;
		}
		if (IsKeyDown(KEY_A)) {
			this->Game->Camera.target.x += deltaTime * 100;
		}
		if (IsKeyDown(KEY_D)) {
			this->Game->Camera.target.x -= deltaTime * 100;
		}
	}

	void Vgameplay::MenuScene::CameraDraw()
	{
		white.DrawRectangle(0, 0, 100, 100);
	}

	void Vgameplay::MenuScene::Draw()
	{
		DrawFPS(0, 0);
		/*white.DrawText("Test string", 0, 0, 20);		
		sprite->Draw(0, 20);*/
	}



