#include "TileReference.h"

TileReference::TileReference(sf::String name, sf::Vector2i graphic_location, const sf::Vector2u& tile_size)
{
	this->setName(name);
	this->setGraphicLocation(graphic_location);
	this->texCoord.push_back(std::vector<sf::Vector2f>(4));
	this->setTexCoords(tile_size);
}

sf::String TileReference::getName() const
{
	return this->name;
}

sf::Vector2i TileReference::get() const
{
	return this->graphic_location;
}

std::string TileReference::to_string() const
{
	return std::string(this->name + " (" + std::to_string(this->graphic_location.x) + ", " + std::to_string(this->graphic_location.y) + ")");
}

void TileReference::setName(sf::String &name)
{
	this->name = name;
}

void TileReference::setGraphicLocation(sf::Vector2i& graphic_location)
{
	this->graphic_location = graphic_location;
}

void TileReference::setTexCoords(const int index, const sf::Vector2u &tile_size)
{
	this->setTexCoords(index, this->graphic_location, tile_size);
}

void TileReference::setTexCoords(const int index, sf::Vector2i& graphic_location, const sf::Vector2u& tile_size)
{
	// Map graphic coordinates to tu and tv
	int tu = graphic_location.x;
	int tv = graphic_location.y;

	// Set the texture coordinates for the 4 points of the quad
	this->texCoord[index].at(0) = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
	this->texCoord[index].at(1) = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
	this->texCoord[index].at(2) = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
	this->texCoord[index].at(3) = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
}

// setTexCoords only have 1 set of coordinates for the base class
void TileReference::setTexCoords(const sf::Vector2u& tile_size)
{
	this->setTexCoords(0, tile_size);
}

std::vector<sf::Vector2f>& TileReference::getTexCoords(const int index)
{
	return this->texCoord[index];
}

std::vector<sf::Vector2f>& TileReference::getTexCoords()
{
	return this->getTexCoords(0);
}

void TileReference::storeQuadReference(sf::Vertex*& quad_pointer)
{
	this->quad_list.push_back(quad_pointer);
}

AnimatedTileReference::AnimatedTileReference(sf::String name, std::vector<sf::Vector2i>&& graphic_location, const sf::Vector2u& tile_size, sf::Uint16 msec_per_frame, const bool& loopback)
{
	this->setName(name);
	this->setGraphicLocation(graphic_location[0]);
	this->msec_per_frame = msec_per_frame;

	// Add additional frames if loop back parameter is given
	if (loopback)
	{
		for (int i = graphic_location.size() - 2; i >= 0; i--)
			graphic_location.push_back(graphic_location.at(i));
	}

	// Create the full list of Texture Coordinates
	for (int i = 0; i < graphic_location.size(); i++) {
		this->texCoord.push_back(std::vector<sf::Vector2f>(4));
		this->setTexCoords(i, graphic_location.at(i), tile_size);
	}
}

std::vector<sf::Vector2f>& AnimatedTileReference::getTexCoords()
{
	return TileReference::getTexCoords(this->frame_value);
}

sf::Uint16 AnimatedTileReference::getTotalFrames()
{
	return this->texCoord.size();
}

void AnimatedTileReference::update(sf::Time elapsed)
{
	this->frame_count_total += elapsed.asMilliseconds();
	sf::Uint16 num_frames = this->getTotalFrames();

	// Update frame value when passing milliseconds per frame
	if (this->frame_count_total >= (frame_value + 1) * this->msec_per_frame)
	{
		// Loop frame count back into valid frame range when exceeding number of frames
		if ((this->frame_count_total / 1000) >= num_frames)
			this->frame_count_total %= (this->msec_per_frame * num_frames);
		
		// Update the frame value
		this->frame_value = this->frame_count_total / 1000;
	}
}