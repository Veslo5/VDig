#pragma once

#include <memory>
#include "../../Vengine/VScene.h"
#include "../../Vengine/VAtlas.h"
#include "../../Vengine/VAnimation.h"
#include"../GridWorld.h"

namespace Vgameplay {
	class GameScene : public Vengine::VScene
	{
	public:
		GameScene(std::string name, Vengine::VGame* game);
		~GameScene() override = default;

		raylib::Camera2D Camera;
		GridWorld MyGridWorld;
		bool startedPainting;

		std::unique_ptr<Vengine::VAtlas>AtlasTest;
		std::unique_ptr<Vengine::VAnimation> AnimTest;
		std::unique_ptr<raylib::RenderTexture> RenderTexture;

		raylib::Color Red = raylib::Color::Red();

		void UnloadContent() override;
		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw() override;

	private:
		
	};

}