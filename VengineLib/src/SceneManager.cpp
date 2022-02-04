#include "../include/SceneManager.h"
#include <algorithm>	

Vengine::SceneManager::SceneManager(VGame* game) : CurrentScene(nullptr), game(game)
{	
}


//void Vengine::SceneManager::AddScene(Scene* scene)
//{
//	ScenesHolder.push_back(scene);
//	if (this->CurrentScene == nullptr)
//	{
//		this->CurrentScene = scene;		
//	}
//}
//
//void Vengine::SceneManager::NextScene(std::string name)
//{
//	CurrentScene->UnloadContent();
//	auto iterator = std::find_if(ScenesHolder.begin(), ScenesHolder.end(), [&name](const Scene* scene) -> bool {return scene->Name == name; });
//	if (iterator != ScenesHolder.end()) {
//				
//		CurrentScene = *iterator;
//		CurrentScene->LoadContent();
//	}
//}
