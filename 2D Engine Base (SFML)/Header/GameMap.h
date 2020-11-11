#pragma once
#include "TileMap.h"
#include <vector>

class GameMap : public sf::Drawable, public sf::Transformable
{
private:
	sf::String name = "Undefined Map";
	TileMap* primary_layer;
	std::vector<TileMap> vec_layer;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	void addLayer(TileMap* tile_map);
	void setPrimaryLayer(TileMap &layer);
	void setMapName(sf::String name);
	bool load();
	sf::String getName();
	TileMap& getPrimaryLayer();
	TileMap& getLayerByIndex(int index);
};