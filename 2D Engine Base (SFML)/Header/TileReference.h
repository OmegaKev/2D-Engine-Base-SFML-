#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TileReference
{
private:
	// Private Variables
	sf::String name = "UNDEFINED";										// Name of the reference tile
	sf::Vector2i graphic_location = sf::Vector2i(-1, -1);				// Holds the starting graphic location
	std::vector<std::vector<sf::Vector2f>> texCoord;					// Holds an vector of size 4 texCoords

	// Private Functions
	void setTexCoords(const int index, const sf::Vector2u& tile_size);	
	std::vector<sf::Vector2f>& getTexCoords(const int index);
public:
	TileReference(sf::String name, sf::Vector2i graphic_location, const sf::Vector2u& tile_size);
	sf::String getName() const;
	sf::Vector2i get() const;
	std::string to_string() const;
	void setTexCoords(const sf::Vector2u& tile_size);
	std::vector<sf::Vector2f>& getTexCoords();
	
};

class AnimatedTileReference : TileReference
{
private:
	sf::Uint16 frame;

};