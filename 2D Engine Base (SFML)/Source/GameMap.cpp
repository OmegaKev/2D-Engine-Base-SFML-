#include "GameMap.h"

void GameMap::addLayer(TileMap* layer)
{
	// Add Layer and make primary if first layer
	this->vec_layer.push_back(std::unique_ptr<TileMap>(layer));
	if (this->primary_layer == NULL)this->setPrimaryLayer(layer);
}

void GameMap::setPrimaryLayer(TileMap* layer)
{
	this->primary_layer = layer;
}

void GameMap::setMapName(sf::String name)
{
	this->name = name;
}

void GameMap::setGameParent(Game* game_parent)
{
	this->game_parent = game_parent;
}

bool GameMap::load()
{
	for (auto& layer : this->vec_layer)
	{
		// TODO: Add Error Message for layers that fail to load
		layer.get()->load();
	}

	return true;
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
	return *this->vec_layer.at(index).get();
}

void GameMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto &layer : this->vec_layer)
	{
		layer.get()->getTileSet()->updateAnimatedTiles(this->game_parent->getClock().getElapsedTime());
		target.draw(*layer.get());
	}
}