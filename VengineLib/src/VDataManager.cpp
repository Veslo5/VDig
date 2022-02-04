#include "../include/VDataManager.h"

void Vengine::VDataManager::LoadAll()
{
	this->TextureHolder.Load();
}

void Vengine::VDataManager::UnloadAll()
{
	this->TextureHolder.UnloadAll();
}