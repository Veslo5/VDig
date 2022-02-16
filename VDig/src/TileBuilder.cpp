#include "TileBuilder.h"

void Vgameplay::TileBuilder::CalculateTiles(Vengine::VPoint currentGridPosition, Vengine::VAtlas* atlas)
{
	//Set starting position until "done" function is called.
	if (isStarted == false)
	{
		defaultStartingPos = currentGridPosition;
		currentEndingPosition = currentGridPosition;
		isStarted = true;
	}

	//Just to check if position was changed
	if (currentEndingPosition == currentGridPosition)
	{
		return;
	}

	SelectedTiles.clear();

	currentEndingPosition = currentGridPosition;


	if (abs(defaultStartingPos.x - currentGridPosition.x) > abs(defaultStartingPos.y - currentGridPosition.y))
	{
		


		float currenPosX;
		float iteratorX;
		bool right;
		//Right movement
		if (defaultStartingPos.x < currentGridPosition.x)
		{
			right = true;
			currenPosX = currentGridPosition.x;
			iteratorX = defaultStartingPos.x;
		}
		else // left movement
		{
			right = false;
			currenPosX = defaultStartingPos.x;
			iteratorX = currentGridPosition.x;
		}


		for (int i = static_cast<int>(iteratorX); i <= currenPosX; ++i)
		{
			int atlasIndex = right ? atlas->GetIndexFromPosition(10, 13) : atlas->GetIndexFromPosition(9, 13);
			SelectedTiles.emplace_back(raylib::Vector2(static_cast<float>(i), defaultStartingPos.y), raylib::Vector2::Zero(), 0, atlasIndex);
		}
	
	}
	else
	{
		
	
		float currenPosY;
		float iteratorY;
		bool top;
		//Down movement
		if (defaultStartingPos.y < currentGridPosition.y)
		{
			top = false;
			currenPosY = currentGridPosition.y;
			iteratorY = defaultStartingPos.y;
		}
		else // Top movement
		{
			top = true;
			currenPosY = defaultStartingPos.y;
			iteratorY = currentGridPosition.y;
		}

		for (int i = static_cast<int>(iteratorY); i <= currenPosY; ++i)
		{
			int atlasIndex = top ? atlas->GetIndexFromPosition(9, 14) : atlas->GetIndexFromPosition(10, 14);
			SelectedTiles.emplace_back(raylib::Vector2(defaultStartingPos.x,  static_cast<float>(i)), raylib::Vector2::Zero(), 0, atlasIndex);
		}

	

	}

	

	//Tile latest = right ? SelectedTiles.back() : SelectedTiles.front();
		/*for (int i = iteratorY; i <= currenPosY; ++i)
		{
			SelectedTiles.emplace_back(raylib::Vector2(latest.GridPosition.x, static_cast<float>(i)), raylib::Vector2::Zero(), 0, top ? atlas->GetIndexFromPosition(9, 14) : atlas->GetIndexFromPosition(10, 14));
		}*/


	
}

void Vgameplay::TileBuilder::EndCalculation()
{
	this->isStarted = false;
	SelectedTiles.clear();
}

int Vgameplay::TileBuilder::CalculateAtlasIndexForTiling(Vengine::VAtlas* atlas, Vgameplay::SelectedTiles selectedTiles)
{
	int atlasPosition = 0;

	int index = 0;

	if (selectedTiles.CenterTile)
	{
		if (selectedTiles.NorthTile && selectedTiles.NorthTile->Type == Vgameplay::TileType::path)
		{
			index += 1;
		}

		if (selectedTiles.EastTile && selectedTiles.EastTile->Type == Vgameplay::TileType::path)
		{
			index += 2;
		}

		if (selectedTiles.SouthTile && selectedTiles.SouthTile->Type == Vgameplay::TileType::path)
		{
			index += 4;
		}

		if (selectedTiles.WestTile && selectedTiles.WestTile->Type == Vgameplay::TileType::path)
		{
			index += 8;
		}
	}

	switch (index)
	{
	default: atlasPosition = atlas->GetIndexFromPosition(9, 15); break;
	case 0: atlasPosition = atlas->GetIndexFromPosition(9, 15); break;
	case 1: atlasPosition = atlas->GetIndexFromPosition(9, 14); break;
	case 2:	atlasPosition = atlas->GetIndexFromPosition(10, 13); break;
	case 3:	atlasPosition = atlas->GetIndexFromPosition(11, 14); break;
	case 4:	atlasPosition = atlas->GetIndexFromPosition(10, 14); break;
	case 5:	atlasPosition = atlas->GetIndexFromPosition(10, 14); break;
	case 6:	atlasPosition = atlas->GetIndexFromPosition(11, 13); break;
	case 7:	atlasPosition = atlas->GetIndexFromPosition(12, 15); break;
	case 8: atlasPosition = atlas->GetIndexFromPosition(9, 13); break;
	case 9:	atlasPosition = atlas->GetIndexFromPosition(12, 14); break;
	case 10:atlasPosition = atlas->GetIndexFromPosition(10, 13); break;
	case 11:atlasPosition = atlas->GetIndexFromPosition(13, 15); break;
	case 12:atlasPosition = atlas->GetIndexFromPosition(12, 13); break;
	case 13:atlasPosition = atlas->GetIndexFromPosition(10, 15); break;
	case 14:atlasPosition = atlas->GetIndexFromPosition(11, 15); break;
	case 15:atlasPosition = atlas->GetIndexFromPosition(9, 15); break;
	}
	return atlasPosition;
}

void Vgameplay::TileBuilder::CalculateTilingForNeighours(Vengine::VAtlas* atlas)
{
}
