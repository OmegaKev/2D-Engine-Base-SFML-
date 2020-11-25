#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow* window_handle;	// Handle to SFML window
	sf::Clock clock;					// SFML Clock
	sf::Vector2u screen_size;			// Screen Size (Reserved for future use)
public:
	Game(sf::RenderWindow *window_handle, sf::Vector2u screen_size);
	sf::Clock& getClock();
};