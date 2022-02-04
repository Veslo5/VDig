#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "raylib-cpp.hpp"
#include "VAtlas.h"
#include "VDataHolder.h"
#include "VAnimation.h"
#include "VPersistentData.h"

namespace Vengine
{


	class VDataManager
	{
	public:
		VDataManager() = default;
		~VDataManager() = default;

		Vengine::VDataHolder<raylib::Texture> TextureHolder;
		Vengine::VDataHolder<Vengine::VPersistentData> PersistentDataHolder;


		void LoadAll();
		void UnloadAll();

	};

}