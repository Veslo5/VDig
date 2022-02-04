#pragma once

#include "raylib-cpp.hpp"
#include "../../Vengine/VScene.h"

namespace Vgameplay {	
	class MenuScene : public Vengine::VScene
	{
	public:
		MenuScene(std::string name, Vengine::VGame* game);
		~MenuScene();

		raylib::Camera2D Camera;

		void UnloadContent() override;
		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw() override;

	private:

		raylib::Color white;
		std::unique_ptr<raylib::Texture2D> sprite;

	};

}