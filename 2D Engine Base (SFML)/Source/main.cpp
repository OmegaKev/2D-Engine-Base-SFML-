#include <SFML/Graphics.hpp>
#include "GameMap.h"
#include "TileMap.h"

int main()
{
	// Set window to size 1000, 1000
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML(2.5.1) 2D Engine");
	
	// Create a basic 64x64 tileset to use with the tile map
	TileSet ts1 = TileSet("Beta1", "Texture/TestTexture1.png", sf::Vector2u(64, 64));
	ts1.addTile(&TileReference("Grass",	sf::Vector2i(0, 0), ts1.getTileSize()));
	ts1.addTile(&TileReference("Rock",	sf::Vector2i(1, 0), ts1.getTileSize()));
	ts1.addTile(&TileReference("Wall1",	sf::Vector2i(2, 0), ts1.getTileSize()));
	ts1.addTile(&TileReference("Wall2",	sf::Vector2i(3, 0), ts1.getTileSize()));
	ts1.addTile(&TileReference("Sand",	sf::Vector2i(0, 1), ts1.getTileSize()));
	ts1.addTile(&TileReference("Water",	sf::Vector2i(1, 1), ts1.getTileSize()));
	
	const int map1[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
						 2, 0, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
						 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2,
						 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
						 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

	// Create a game map and add the tilemap as the first layer
	GameMap gm1 = GameMap();
	gm1.addLayer(&TileMap(&ts1, map1, sf::Vector2u(16, 5)));
	gm1.load();

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
		window.draw(gm1);
		window.display();
	}
	return 0;
}