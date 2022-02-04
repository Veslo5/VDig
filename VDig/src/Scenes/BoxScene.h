#pragma once

#include "VScene.h"


namespace Vgameplay {
	class BoxScene : public Vengine::VScene
	{
	public:
		BoxScene(std::string name, Vengine::VGame* game);
		~BoxScene();

		void UnloadContent() override;
		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw() override;

	};

}
