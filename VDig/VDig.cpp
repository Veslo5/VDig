#include "raylib-cpp.hpp"
#include "Vengine/VGame.h"
#include "VGameplay/Scenes/MenuScene.h"

int main() {

	{
		const auto game = std::make_unique<Vengine::VGame>(800, 600, "Hello", raylib::Color::Black());		

		game->Run();
	}

	return 0;
}

