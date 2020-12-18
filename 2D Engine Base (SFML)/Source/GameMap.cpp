#include "GameMap.h"

void GameMap::addLayer(TileMap* layer)
{
	// Add Layer and make primary if first layer
	this->vec_layer.push_back(std::unique_ptr<TileMap>(layer));
	if (this->primary_layer == NULL)this->setPrimaryLayer(layer);

	// All Cameras should be defined by this point
	// The number of views should be equivalent to the number of layers
	if(this->vec_layer.size() > 1)
		this->game_parent->getCamera()->addView();
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
	// TODO: Iterate through all cameras defined in Game instead of just 1 Camera
	for (size_t i = 0; i < this->vec_layer.size(); i++)
	{
		TileMap* p_tm = this->vec_layer[i].get();
		
		p_tm->getTileSet()->updateAnimatedTiles(this->game_parent->getClock().getElapsedTime());
		this->game_parent->getWindowHandle()->setView(*this->game_parent->getCamera()->getView(i));
		target.draw(*p_tm);
	}
}