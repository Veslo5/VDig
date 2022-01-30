#pragma once

#include <string>
#include <iostream>


namespace Vengine {
	class VGame; // forward declaration
	class Scene
	{
	public:
		Scene(std::string name, VGame* game);
		virtual ~Scene();

		std::string Name;


		virtual void UnloadContent() = 0;
		virtual void LoadContent() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void CameraDraw() = 0;
		virtual void Draw() = 0;

	private:

	protected:
		VGame* Game;

	};
}