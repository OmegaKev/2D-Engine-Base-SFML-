#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameMap.h"
#include "TileMap.h"
#include <memory>

int main()
{
	// Set window to size 1000, 1000
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML(2.5.1) 2D Engine");
	
	// Create a basic 64x64 tileset to use with the tile map
	TileSet ts1 = TileSet("Beta1", "Texture/TestTexture1.png", sf::Vector2u(64, 64));
	ts1.addTile(new TileReference("Grass",	sf::Vector2i(0, 0), ts1.getTileSize()));
	ts1.addTile(new TileReference("Rock",	sf::Vector2i(1, 0), ts1.getTileSize()));
	ts1.addTile(new TileReference("Wall1",	sf::Vector2i(2, 0), ts1.getTileSize()));
	ts1.addTile(new TileReference("Wall2",	sf::Vector2i(3, 0), ts1.getTileSize()));
	ts1.addTile(new TileReference("Sand",	sf::Vector2i(0, 1), ts1.getTileSize()));
	ts1.addTile(new TileReference("Water",	sf::Vector2i(1, 1), ts1.getTileSize()));
	
	// Animated Tile
	ts1.addTile(new AnimatedTileReference("Clock1t5A", { sf::Vector2i(0, 2), sf::Vector2i(1, 2), sf::Vector2i(2, 2), sf::Vector2i(3, 2), sf::Vector2i(4, 2) }, ts1.getTileSize(), sf::Uint16(500), true));
	ts1.addTile(new AnimatedTileReference("Clock1t5B", { sf::Vector2i(0, 2), sf::Vector2i(1, 2), sf::Vector2i(2, 2), sf::Vector2i(3, 2), sf::Vector2i(4, 2) }, ts1.getTileSize(), sf::Uint16(1000), false));


	RawMap *map1 = new RawMap();
	map1->setMapData({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
					   2, 0, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
					   2, 0, 0, 0, 0, 0, 0, 6, 7, 6, 3, 0, 0, 0, 0, 2,
					   2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
					   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 });
	
	map1->setSize(sf::Vector2u(16, 5));

	// Create a game map and add the tilemap as the first layer
	GameMap gm1 = GameMap();
	gm1.addLayer(new TileMap(&ts1, map1, sf::Vector2u(16, 5)));
	gm1.load();

	// Our Game object
	Game game = Game(&window, sf::Vector2u(16, 5));
	gm1.setGameParent(&game);

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
		game.getClock().restart();
	}

	return 0;
}