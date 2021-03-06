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

// Store the list reference and increase the instance count
void TileReference::storeQuadReference(sf::Vertex*& quad_pointer)
{
	this->quad_list.push_back(quad_pointer);
	this->instance_count++;
}

// Null the list reference and reduce the instance count
void TileReference::removeQuadReference(const sf::Uint64& index)
{
	this->quad_list[index] = NULL;
	this->instance_count--;
}

// Get the number of tile instances invoked from this tile reference
sf::Uint64 TileReference::getInstanceCount() const
{
	return this->instance_count;
}

// Return the normal size including NULL elements
sf::Uint64 TileReference::getQrSize() const
{
	return this->quad_list.size();
}

AnimatedTileReference::AnimatedTileReference(sf::String name, std::vector<sf::Vector2i>&& graphic_location, const sf::Vector2u& tile_size, sf::Uint16 msec_per_frame, const bool& loopback)
{
	this->setName(name);
	this->setGraphicLocation(graphic_location[0]);
	this->msec_per_frame = msec_per_frame;

	// Add additional frames if loop back parameter is given
	if (loopback)
	{
		for (int i = graphic_location.size() - 2; i >= 1; i--)
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

void AnimatedTileReference::update(const sf::Time &elapsed)
{
	this->elapsed_frames += elapsed;
	sf::Uint32 frame_count_total = this->elapsed_frames.asMilliseconds();
	sf::Uint16 num_frames = this->getTotalFrames();

	// Update frame value when passing milliseconds per frame
	if (frame_count_total >= (this->frame_value + 1) * this->msec_per_frame)
	{
		// Loop frame count back into valid frame range when exceeding number of frames
		if ((frame_count_total / this->msec_per_frame) >= num_frames)
		{
			frame_count_total %= this->msec_per_frame * num_frames;
			this->elapsed_frames = sf::milliseconds(frame_count_total);
		}
		
		// Update the frame value
		this->frame_value = frame_count_total / this->msec_per_frame;
		this->updateQuadTextures(this->frame_value);	
	}
}

void AnimatedTileReference::updateQuadTextures(const int &index)
{
	if (index >= this->texCoord.size())
	{
		std::cout << "Error: Invalid Frame Given: " + index << std::endl;
		return;
	}
	// Update all the quads referenced in quad list
	for (auto& quad : quad_list)
	{
		// Skip removed quads
		if (quad == NULL)continue;

		quad[0].texCoords = TileReference::getTexCoords(index).at(0);
		quad[1].texCoords = TileReference::getTexCoords(index).at(1);
		quad[2].texCoords = TileReference::getTexCoords(index).at(2);
		quad[3].texCoords = TileReference::getTexCoords(index).at(3);
	}
}