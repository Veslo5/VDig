#pragma once

#include "VScene.h"
#include <memory>
#include <stack>
#include <string>


namespace Vengine {
	class VGame;
	class SceneManager
	{
	public:
		SceneManager(VGame* game);
		~SceneManager() = default;

		std::unique_ptr<VScene> CurrentScene;
		std::unique_ptr<VScene> FutureScene;

		std::stack<std::unique_ptr<VScene>> ScenesHolder;
		bool ChangeSceneNextFrame;


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
			this->ChangeSceneNextFrame = true;
			FutureScene = std::make_unique<T>(name, game);
		}

	}
}

