#pragma once
#include "TileMap.h"
#include <vector>

class GameMap
{
private:
	sf::String name = "Undefined Map";
	TileMap* primary_layer;
	std::vector<TileMap> vec_layer;
public:
	void addLayer(TileMap& tile_map);
	void setPrimaryLayer(TileMap &layer);
	void setMapName(sf::String name);
	sf::String getName();
	TileMap& getPrimaryLayer();
	TileMap& getLayerByIndex(int index);
};