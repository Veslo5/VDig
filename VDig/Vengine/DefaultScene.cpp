#include "DefaultScene.h"
#include "../VGameplay/Scenes/MenuScene.h"
#include "VGame.h"


DefaultScene::DefaultScene(std::string name, Vengine::VGame* game) : VScene(name, game), Logo("res/logo.png"),
countdown(1.5f, [this]() { TimerCallback(); }, false), LogoTy(0)

{
}

DefaultScene::~DefaultScene() = default;

void DefaultScene::TimerCallback()
{
	//TODO: this must be independent of Vgameplay!
	Game->SceneManager.ChangeScene<Vgameplay::MenuScene>("Menu");
}

void DefaultScene::UnloadContent()
{

}

void DefaultScene::LoadContent()
{
	Tween = tweeny::from(0 - Logo.height * 2).to(0).during(1000).via(tweeny::easing::bounceOut);
}

void DefaultScene::Update(float deltaTime)
{
	this->Game->Camera.SetZoom(this->Game->WindowWidth / 1366.f);
	this->Game->Camera.SetOffset(raylib::Vector2(this->Game->WindowWidth / 2, this->Game->WindowHeight / 2));
	this->Game->Camera.SetTarget(raylib::Vector2(Logo.width / 2, Logo.height / 2));

	LogoTy = Tween.step(deltaTime);

	countdown.Update(deltaTime);
}

void DefaultScene::CameraDraw()
{
	Logo.Draw(0, LogoTy);
}

void DefaultScene::Draw()
{
}

