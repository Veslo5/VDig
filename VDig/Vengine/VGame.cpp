#include "VGame.h"
#include "raylib-cpp.hpp"
#include "DefaultScene.h"

Vengine::VGame::VGame(int width, int height, std::string caption, raylib::Color clearColor) : WindowWidth(width), WindowHeight(height), Caption(caption),
ClearColor(clearColor),
Window(width, height, caption, true), SceneManager(this), DataManager()
{
}

Vengine::VGame::~VGame() = default;


void Vengine::VGame::Run()
{
	Window.Init(this->WindowWidth, this->WindowHeight, this->Caption);

	SetTargetFPS(60);
	Window.SetState(FLAG_WINDOW_RESIZABLE);
	Window.SetState(FLAG_VSYNC_HINT);


	if (this->WindowWidth == 0 && this->WindowHeight == 0)
	{
		ToggleFullscreen();
		this->WindowWidth = GetScreenWidth();
		this->WindowHeight = GetScreenHeight();
	}


	SceneManager.ChangeScene<DefaultScene>("Default");

	// Loading before game loop
	SceneManager.CurrentScene->LoadContent();

	while (!Window.ShouldClose()) {

		if (IsWindowResized())
		{
			this->WindowWidth = GetScreenWidth();
			this->WindowHeight = GetScreenHeight();
			TraceLog(LOG_INFO, "WINDOW: RESIZED");
		}

		if (this->SceneManager.ChangeSceneNextFrame == true)
		{
			SceneManager.CurrentScene->UnloadContent();
			SceneManager.CurrentScene = std::move(SceneManager.FutureScene);
			SceneManager.CurrentScene->LoadContent();
			this->SceneManager.ChangeSceneNextFrame = false;
		}

		SceneManager.CurrentScene->Update(GetFrameTime());

		SceneManager.CurrentScene->Draw();

	}


}

void Vengine::VGame::ClearBackground()
{
	Window.ClearBackground(this->ClearColor);
}
