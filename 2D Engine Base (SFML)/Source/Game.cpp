#include "Game.h"

sf::Clock& Game::getClock()
{
	return this->clock;
}

Game::Game(sf::RenderWindow * window_handle, sf::Vector2u screen_size)
{
	this->window_handle = window_handle;
	this->screen_size = screen_size;
}