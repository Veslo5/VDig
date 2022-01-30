#include "VGame.h"
#include "raylib-cpp.hpp"
#include <stdexcept>



Vengine::VGame::VGame(int width, int height, std::string caption, raylib::Color clearColor) : WindowWidth(width), WindowHeight(height), Caption(caption), Camera(),
																							  ClearColor(clearColor), SceneManager(this),
																							  Window(width,height, caption, true) // lateInitialization
{
	if (this->WindowWidth == 0 && this->WindowHeight == 0)
	{
		this->WindowWidth = GetScreenWidth();
		this->WindowHeight = GetScreenHeight();
	}


}

Vengine::VGame::~VGame() = default;


void Vengine::VGame::Run()
{
	if (SceneManager.CurrentScene == nullptr)
	{
		throw std::runtime_error("Default scene must be provided!");
	}

	Window.Init(this->WindowWidth, this->WindowHeight, this->Caption);
	SetTargetFPS(60);	

	Window.SetState(FLAG_WINDOW_RESIZABLE);

	SceneManager.CurrentScene->LoadContent();

	while (!Window.ShouldClose()) {

		SceneManager.CurrentScene->Update(GetFrameTime());

		BeginDrawing();
			Window.ClearBackground(this->ClearColor);

			this->Camera.BeginMode();
			SceneManager.CurrentScene->CameraDraw();
			this->Camera.EndMode();

			SceneManager.CurrentScene->Draw();
		EndDrawing();
	}


}
