#include <SFML/Graphics.hpp>
#include "TileMap.h"

int main()
{
	// Set window to size 1000, 1000
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML(2.5.1) 2D Engine");

	const int ts[] = { 2, 2, 2, 2, 2,
					   2, 0, 3, 3, 2,
					   2, 0, 0, 3, 2,
					   2, 0, 0, 0, 2,
					   2, 2, 2, 2, 2 };

	TileMap m1 = TileMap();
	m1.load("Texture/TestTexture1.png", sf::Vector2u(64, 64), ts, sf::Vector2u(5, 5));

	// Main SFML Loop
	while (window.isOpen())
	{
		// Check for SFML events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)window.close();
		}

		// Draw to the window after clearing the frame
		window.clear();
		window.draw(m1);
		window.display();
	}
	return 0;
}