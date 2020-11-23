#include "TileSet.h"

TileSet::TileSet(sf::String name, sf::String file_location, sf::Vector2u tile_size)
{
	this->tileset_name = name;
	this->file_location = file_location;
	this->tile_size = tile_size;
}

// Returns the file location string
sf::String TileSet::getFileLocation()
{
	return this->file_location;
}

// Returns the name of the tileset
sf::String TileSet::getName()
{
	return this->tileset_name;
}

// Returns the tile size as an unsigned integer pair
sf::Vector2u TileSet::getTileSize()
{
	return this->tile_size;
}

// Returns a reference to the tile at the index
std::shared_ptr<TileReference>& TileSet::getTile(int index)
{
	return this->t_ref.at(index);
}

void TileSet::addTile(TileReference* tile)
{
	std::shared_ptr<TileReference> sp_tile = std::shared_ptr<TileReference>(tile);
	this->t_ref.push_back(sp_tile);

	// Check if tile is animated and add it to the animated tile vector if so.
	if (dynamic_cast<AnimatedTileReference*>(tile) != NULL)
		this->at_ref.push_back(sp_tile);
		
}

void TileSet::updateAnimatedTiles(const sf::Time& elapsed)
{
	for (auto& anim_tile : this->at_ref)
		dynamic_cast<AnimatedTileReference*>(anim_tile.get())->update(elapsed);
}