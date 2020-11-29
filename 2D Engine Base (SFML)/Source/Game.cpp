#include "Game.h"

Game::Game(sf::RenderWindow* window_handle, const sf::Vector2u& screen_size)
{
	this->setWindowHandle(window_handle);
	this->setScreenSize(screen_size);
}

void Game::setWindowHandle(sf::RenderWindow* window_handle)
{
	this->window_handle = window_handle;
}

void Game::setScreenSize(const sf::Vector2u& screen_size)
{
	this->screen_size = screen_size;
}

void Game::createCamera(Camera* camera_handle)
{
	// TODO: Facilitate the creation and management of multiple cameras(views)
	this->camera_handle = std::unique_ptr<Camera>(camera_handle);
	this->camera_handle->setParent(this);
}

sf::Clock& Game::getClock()
{
	return this->clock;
}

sf::RenderWindow* Game::getWindowHandle() const
{
	return this->window_handle;
}

sf::View* Game::getViewHandle() const
{
	return this->camera_handle->getView();
}

sf::Vector2u Game::getScreenSize() const
{
	return this->screen_size;
}

Camera* Game::getCamera() const
{
	return this->camera_handle.get()->type();
}