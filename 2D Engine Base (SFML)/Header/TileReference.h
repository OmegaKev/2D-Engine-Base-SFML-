#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class TileReference
{
private:
	// Private Variables
	sf::String name = "UNDEFINED";										// Name of the reference tile
	sf::Vector2i graphic_location = sf::Vector2i(-1, -1);				// Holds the starting graphic location
	sf::Uint64 instance_count = 0;
protected:
	// Protected
	std::vector<sf::Vertex*> quad_list = std::vector<sf::Vertex*>();	// Hold a pointer to every quad that uses this tile

	TileReference() {};
	std::vector<std::vector<sf::Vector2f>> texCoord;					// Holds an vector of size 4 texCoords

	std::vector<sf::Vector2f>& getTexCoords(const int index);
	void setTexCoords(const int index, const sf::Vector2u& tile_size);
	void setTexCoords(const int index, sf::Vector2i& graphic_location, const sf::Vector2u& tile_size);
	
public:
	TileReference(sf::String name, sf::Vector2i graphic_location, const sf::Vector2u& tile_size);
	virtual ~TileReference() {};
	sf::String getName() const;
	sf::Vector2i get() const;
	std::string to_string() const;
	void setTexCoords(const sf::Vector2u& tile_size);
	std::vector<sf::Vector2f>& getTexCoords();	
	void setName(sf::String& name);
	void setGraphicLocation(sf::Vector2i& graphic_location);
	void storeQuadReference(sf::Vertex*& quad_pointer);
	void removeQuadReference(const sf::Uint64 &index);
	sf::Uint64 getInstanceCount() const;
	sf::Uint64 getQrSize() const;
};

class AnimatedTileReference : public TileReference
{
private:
	sf::Uint16 msec_per_frame;						// How many milliseconds before we advance the frame
	sf::Uint16 frame_value = 0;						// Holds the current frame value
	sf::Time elapsed_frames;						// Holds the frame count total

	void updateQuadTextures(const int& index);		// Update all quad references stored by this animated tile
public:
	AnimatedTileReference(sf::String name, std::vector<sf::Vector2i> &&graphic_location, const sf::Vector2u& tile_size, sf::Uint16 msec_per_frame, const bool& loopback = false);
	std::vector<sf::Vector2f>& getTexCoords();
	sf::Uint16 getTotalFrames();
	void update(const sf::Time &elapsed);
};