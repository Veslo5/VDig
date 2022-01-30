#pragma once

#include "Scene.h"
#include <memory>
#include <stack>
#include <string>


namespace Vengine {
	class VGame;
	class SceneManager
	{
	public:
		SceneManager(VGame* game);
		~SceneManager();

		std::unique_ptr<Scene> CurrentScene;
		std::stack<std::unique_ptr<Scene>> ScenesHolder;

		template <typename T>
		void AddSceneStack(std::string name);

		template <typename T>
		void PopScene(std::string name);

		template <typename T>
		void ChangeScene(std::string name);
	private:

		VGame* game;
	};

	template<typename T>
	inline void SceneManager::AddSceneStack(std::string name)
	{
		ScenesHolder.push(std::make_unique<T>(name, game));
	}

	template<typename T>
	inline void SceneManager::PopScene(std::string name)
	{
		ScenesHolder.pop();
	}

	template<typename T>
	inline void SceneManager::ChangeScene(std::string name)
	{
		if (CurrentScene == nullptr)
		{
			CurrentScene = std::make_unique<T>(name, game);
			//Load must be after opengl context creation. 
			//So it is in VGame->Run();
		}
		else
		{
			CurrentScene->UnloadContent();
			CurrentScene = std::make_unique<T>(name, game);
			CurrentScene->LoadContent();
		}

	}
}

