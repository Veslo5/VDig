#include "../include/DefaultScene.h"
#include "../include/VGame.h"

DefaultScene::DefaultScene(std::string name, Vengine::VGame* game) : VScene(name, game), Logo("res/logo.png"),
countdown(1.5f, [this]() { TimerCallback(); }, false), LogoTy(0)

{
}

void DefaultScene::TimerCallback()
{
	this->Game->SceneManager.ChangeSceneNextFrame = true;
}

void DefaultScene::UnloadContent()
{

}

void DefaultScene::LoadContent()
{
	/*this->Game->DataManager.TextureHolder.AddToLoadingQueue("res/test.png");
	this->Game->DataManager.Load();
	auto texture = this->Game->DataManager.GetTexture("res/test.png");*/



	Tween = tweeny::from(0 - Logo.height * 2).to(0).during(1000).via(tweeny::easing::bounceOut);
}

void DefaultScene::Update(float deltaTime)
{
	this->Camera.SetZoom(this->Game->WindowWidth / 1366.f);
	this->Camera.SetOffset(raylib::Vector2(this->Game->WindowWidth / 2, this->Game->WindowHeight / 2));
	this->Camera.SetTarget(raylib::Vector2(Logo.width / 2, Logo.height / 2));

	LogoTy = Tween.step(deltaTime);

	countdown.Update(deltaTime);
}

void DefaultScene::Draw()
{
	BeginDrawing();
	Game->ClearBackground();

	Camera.BeginMode();
	Logo.Draw(0, LogoTy);
	Camera.EndMode();

	EndDrawing();
}

