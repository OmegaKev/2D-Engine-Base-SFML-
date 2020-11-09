#include <SFML/Graphics.hpp>
#include "TileMap.h"

int main()
{
	// Set window to size 1000, 1000
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML(2.5.1) 2D Engine");
	
	// Create a basic 64x64 tileset to use with the tile map
	TileSet t1 = TileSet("Beta1", "Texture/TestTexture1.png", sf::Vector2u(64, 64));
	t1.addTile(&TileReference("Grass",	sf::Vector2i(0, 0)));
	t1.addTile(&TileReference("Rock",	sf::Vector2i(1, 0)));
	t1.addTile(&TileReference("Wall1",	sf::Vector2i(2, 0)));
	t1.addTile(&TileReference("Wall2",	sf::Vector2i(3, 0)));
	t1.addTile(&TileReference("Sand",	sf::Vector2i(0, 1)));
	t1.addTile(&TileReference("Water",	sf::Vector2i(1, 1)));
	
	const int map1[] = { 2, 2, 2, 2, 2,
						 2, 0, 3, 3, 2,
						 2, 0, 0, 3, 2,
						 2, 0, 0, 0, 2,
						 2, 2, 2, 2, 2 };

	TileMap m1 = TileMap(&t1, map1, sf::Vector2u(5, 5));
	m1.load();

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