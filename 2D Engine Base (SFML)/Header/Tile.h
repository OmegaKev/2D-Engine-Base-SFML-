#pragma once
#include <SFML/Graphics.hpp>

class TileReference
{
private:
	sf::String name = "UNDEFINED";
	sf::Vector2i graphic_location = sf::Vector2i(-1, -1);
public:
	TileReference(sf::String name, sf::Vector2i graphic_location);
	sf::Vector2i get();
};