#pragma once

#include "raylib-cpp.hpp"
#include "../../Vengine/Scene.h"

namespace Vgameplay {	
	class MenuScene : public Vengine::Scene
	{
	public:
		MenuScene(std::string name, Vengine::VGame* game);
		~MenuScene();

		void UnloadContent() override;
		void LoadContent() override;
		void Update(float deltaTime) override;
		void CameraDraw () override;
		void Draw() override;

	private:
		
		raylib::Color white;
		std::unique_ptr<raylib::Texture2D> sprite;

	};

}