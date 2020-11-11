#include "GameMap.h"

void GameMap::addLayer(TileMap& layer)
{
	// Add Layer and make primary if first layer
	this->vec_layer.push_back(layer);
	if (this->primary_layer == NULL)this->setPrimaryLayer(layer);
}

void GameMap::setPrimaryLayer(TileMap& layer)
{
	this->primary_layer = &layer;
}

void GameMap::setMapName(sf::String name)
{
	this->name = name;
}

sf::String GameMap::getName()
{
	return this->name;
}

TileMap& GameMap::getPrimaryLayer()
{
	return *this->primary_layer;
}

TileMap& GameMap::getLayerByIndex(int index)
{
	return this->vec_layer.at(index);
}