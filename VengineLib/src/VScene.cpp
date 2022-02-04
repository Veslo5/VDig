#include "../include/VScene.h"
#include "raylib-cpp.hpp"

Vengine::VScene::VScene(std::string name, VGame* game) : Name(name), Game(game)
{
	TraceLog(LOG_INFO, ("SCENE: LOADED " + name).c_str());
}

Vengine::VScene::~VScene()
{
	TraceLog(LOG_INFO, ("SCENE: UNLOADED " + Name).c_str());
}
