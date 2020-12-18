#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"

class Camera; // Forward Declaration of Camera

class Game
{
private:
	sf::RenderWindow* window_handle;		// Handle to SFML window
	std::unique_ptr<Camera> camera_handle;	// Hold our camera
	sf::Clock clock;						// SFML Clock
	sf::Vector2u screen_size;				// Screen Size (Reserved for future use)
public:
	Game(sf::RenderWindow* window_handle, const sf::Vector2u& screen_size);
	void setWindowHandle(sf::RenderWindow* window_handle);
	void setScreenSize(const sf::Vector2u& screen_size);
	void createCamera(Camera* camera_handle);
	
	sf::Clock& getClock();
	sf::RenderWindow* getWindowHandle() const;
	sf::Vector2u getScreenSize() const;
	Camera* getCamera() const;
};