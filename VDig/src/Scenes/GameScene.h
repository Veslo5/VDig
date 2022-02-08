#pragma once

#include <memory>
#include "VScene.h"
#include "VAtlas.h"
#include "VAnimation.h"
#include "../GridWorld.h"
#include "../AStar/AStar.hpp"
#include <future>

namespace Vgameplay {
	class GameScene : public Vengine::VScene
	{
	public:
		GameScene(std::string name, Vengine::VGame* game);
		~GameScene() override = default;

		raylib::Camera2D Camera;
		GridWorld MyGridWorld;
		bool startedPainting;
		AStar::Generator PathFinder;


		std::unique_ptr<Vengine::VAtlas>AtlasTest;
		std::unique_ptr<Vengine::VAnimation> AnimTest;
		std::unique_ptr<Vengine::VAtlas> GameTileSet;
		std::unique_ptr<raylib::RenderTexture> RenderTexture;

		raylib::Color Red = raylib::Color::Red();


		void UnloadContent() override;
		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw() override;

	private:
		void generateGrid();
		void loadPath();
		float cameraZoom = 0.f;
		std::future<void> task;
	};

}