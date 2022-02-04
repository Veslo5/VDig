#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "raylib-cpp.hpp"

namespace Vengine
{
	template <typename T>
	class VDataHolder
	{
	public:
		VDataHolder() = default;
		~VDataHolder() = default;

		void AddToLoadingQueue(const std::string& path);
		void Load();
		void Unload(const std::string& path);
		void UnloadAll();
		std::shared_ptr<T> GetTexture(const std::string& path);

	private:
		std::unordered_map<std::string, std::shared_ptr<T>> LoadedTextures;
		std::vector<std::string> ToLoad;

	};

	template <typename T>
	void VDataHolder<T>::AddToLoadingQueue(const std::string& path)
	{
		ToLoad.push_back(path);
	}

	template <typename T>
	void VDataHolder<T>::Load()
	{
		for (const std::string& load : ToLoad)
		{
			LoadedTextures.try_emplace(load, std::make_shared<T>(load));
		}

		ToLoad.clear();
	}

	template <typename T>
	void VDataHolder<T>::Unload(const std::string& path)
	{
		LoadedTextures.erase(path);

	}

	template <typename T>
	void VDataHolder<T>::UnloadAll()
	{
		LoadedTextures.clear();
	}

	template <typename T>
	std::shared_ptr<T> VDataHolder<T>::GetTexture(const std::string& path)
	{
		return LoadedTextures.at(path);
	}
}
