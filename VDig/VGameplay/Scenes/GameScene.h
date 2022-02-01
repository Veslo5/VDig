#pragma once

#include "../../Vengine/VScene.h"
#include "../../Vengine/VAtlas.h"
#include "../../Vengine/VAnimation.h"
#include"../GridWorld.h"

namespace Vgameplay {
	class GameScene : public Vengine::VScene
	{
	public:
		GameScene(std::string name, Vengine::VGame* game);
		~GameScene();

		GridWorld MyGridWorld;
		raylib::RenderTexture RenderTexture;
		Vengine::VAtlas AtlasTest;
		Vengine::VAnimation AnimTest;


		raylib::Color Red = raylib::Color::Red();

		void UnloadContent() override;
		void LoadContent() override;
		void Update(float deltaTime) override;
		void CameraDraw() override;
		void Draw() override;

	private:
		
	};

}