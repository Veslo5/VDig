#pragma once

#include "VScene.h"
#include "VTimer.h"
#include "tweeny-3.2.0.h"
#include "raylib-cpp.hpp"

class DefaultScene : public Vengine::VScene
{
public:
	DefaultScene(std::string name, Vengine::VGame* game);
	~DefaultScene();

	raylib::Texture2D Logo;
	tweeny::tween<int> Tween;
	Vengine::VTimer countdown;
	int LogoTy;


	void TimerCallback();

	void UnloadContent() override;
	void LoadContent() override;
	void Update(float deltaTime) override;
	void CameraDraw() override;
	void Draw() override;
};
