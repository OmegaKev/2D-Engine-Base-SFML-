#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow* window_handle;
	sf::Clock clock;
	sf::Vector2u screen_size;
public:
	Game(sf::RenderWindow *window_handle, sf::Vector2u screen_size);
	sf::Clock& getClock();
};