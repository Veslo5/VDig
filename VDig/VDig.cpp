#include "raylib-cpp.hpp"
#include "VGame.h"
#include "src/Scenes/MenuScene.h"

int main() {

	{
		const auto game = std::make_unique<Vengine::VGame>(800, 600, "Hello", raylib::Color(14,7,27));		
		game->SceneManager.SetFirstScene<Vgameplay::MenuScene>("MenuScene");

		game->Run();
	}

	return 0;
}

 