#pragma once

#include "Tile.h"
#include <vector>
#include <memory>


namespace Vgameplay
{
	class GridWorld
	{
	public:
		GridWorld(int width, int height, int size, int spacing);
		~GridWorld() = default;

		/**
		 * \brief Size of tile (in pixels)
		 */
		const int TilesSize;

		/**
		 * \brief Width of grid world (in tiles)
		 */
		int Width;

		/**
		 * \brief Height of grid world (in tiles)
		 */
		int Height;

		/**
		 * \brief Return grid width in pixel size
		 * \return grid width in pixel size
		 */
		int GetPixelSizeX() const;

		/**
		 * \brief Return grid height in pixel size
		 * \return grid height in pixel size
		 */
		int GetPixelSizeY() const;

		/**
		 * \brief Container with unique tiles
		 */
		std::vector<std::unique_ptr<Tile>> TileWorld;

		/**
		 * \brief Safe tile data changing
		 * \param gridPosition WARNING: gridPosition must be rounded!
		 * \param newAtlasPosition atlas sprite index
		 * \return true if data changed successfully, false if not
		 */
		bool SetTileDataGridPos(raylib::Vector2 gridPosition, int newAtlasPosition);

		/**
		 * \brief Safe tile data changing
		 * \param worldPosition world position coordinates
		 * \param newAtlasPosition atlas sprite index
		 * \return true if data changed successfully, false if not
		 */
		bool SetTileDataWorldPos(raylib::Vector2 worldPosition, int newAtlasPosition);

		/**
		 * \brief Check if tile exists on grid coordinates
		 * \param gridPosition WARNING: gridPosition must be rounded!
		 * \return true if exists, false if not
		 */
		bool IsTileExistOnGridPos(raylib::Vector2 gridPosition) const;

		/**
		 * \brief Gets tile at grid position
		 * \param gridPosition WARNING: gridPosition must be rounded!
		 * \return Weak pointer to Tile object from TileWorld, if no tile is found, nullptr is returned
		 */
		Tile* GetTileAtGridPos(raylib::Vector2 gridPosition) const;

		/**
		 * \brief Gets tile by world coordinates
		 * \param worldPosition World coordinates
		 * \return Weak pointer to Tile object from TileWorld, if no tile is found, nullptr is returned
		 */
		Tile* GetTileAtWorldPos(raylib::Vector2 worldPosition) const;

		/**
		 * \brief Gets tile at grid position by mathematical calculation
		 * \param gridPosition WARNING: gridPosition should be rounded!
		 * \return Weak pointer to Tile object from TileWorld, if no tile is found, nullptr is returned
		 */
		Tile* GetTileAtGridPosIndex(raylib::Vector2 gridPosition) const;

		/**
		 * \brief Convert grid position to world position
		 * \param gridPosition WARNING: gridPosition must be rounded!
		 * \return world coordinates
		 */
		raylib::Vector2 GetWorldPositionFromGridPosition(raylib::Vector2 gridPosition) const;

		/**
		 * \brief Convert world position to grid position
		 * \param worldPosition world coordinates
		 * \return grid coordinates
		 */
		raylib::Vector2 GetGridPositionFromWorldPosition(raylib::Vector2 worldPosition) const;

	};


}