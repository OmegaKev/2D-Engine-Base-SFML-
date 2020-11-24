#pragma once
#include "TileMap.h"
#include "Game.h"
#include <vector>

class GameMap : public sf::Drawable, public sf::Transformable
{
private:
	Game* game_parent;										// Game parent pointer					
	sf::String name = "Undefined Map";						// Name of Map
	TileMap* primary_layer;									// Pointer to primary layer (Usually 0 Layer)
	std::vector<std::unique_ptr<TileMap>> vec_layer;		// Holds all the Tilemap Layers
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	void addLayer(TileMap* tile_map);
	void setPrimaryLayer(TileMap *layer);
	void setMapName(sf::String name);
	void setGameParent(Game* game_parent);
	bool load();
	sf::String getName();
	TileMap& getPrimaryLayer();
	TileMap& getLayerByIndex(int index);
};