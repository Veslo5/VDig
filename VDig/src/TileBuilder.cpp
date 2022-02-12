#include "TileBuilder.h"

void Vgameplay::TileBuilder::CalculateTiles(raylib::Vector2 currentGridPosition)
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

	int currenPosX;
	int iteratorX;
	bool rigth;
	//Right movement
	if (defaultStartingPos.x < currentGridPosition.x)
	{
		rigth = true;
		currenPosX = static_cast<int>(currentGridPosition.x);
		iteratorX = static_cast<int>(defaultStartingPos.x);
	}
	else // left movement
	{
		rigth = false;
		currenPosX = static_cast<int>(defaultStartingPos.x);
		iteratorX = static_cast<int>(currentGridPosition.x);
	}

	for (int i = iteratorX; i <= currenPosX; ++i)
	{
		SelectedTiles.emplace_back(static_cast<float>(i), defaultStartingPos.y);
	}

	raylib::Vector2 latest = rigth ? SelectedTiles.back() : SelectedTiles.front();

	int currenPosY;
	int iteratorY;
	//Down movement
	if (defaultStartingPos.y < currentGridPosition.y)
	{
		currenPosY = static_cast<int>(currentGridPosition.y);
		iteratorY = static_cast<int>(defaultStartingPos.y);
	}
	else // Top movement
	{
		currenPosY = static_cast<int>(defaultStartingPos.y);
		iteratorY = static_cast<int>(currentGridPosition.y);
	}

	for (int i = iteratorY; i <= currenPosY; ++i)
	{
		SelectedTiles.emplace_back(latest.x, static_cast<float>(i));
	}
}

void Vgameplay::TileBuilder::EndCalculation()
{
	this->isStarted = false;
	SelectedTiles.clear();
}
