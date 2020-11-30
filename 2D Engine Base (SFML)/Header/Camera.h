#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

class Game; // Forward Declaration of Game

// Base Camera Class
class Camera : public sf::Drawable, public sf::Transformable
{
private:
	const Game *game_parent;
	sf::String name;
	sf::View *view;
	float speed = 3.0f;
public:
	Camera(const sf::String& name, sf::View* view);
	Camera(const sf::String& name, const Game* game_parent, sf::View* view);
	virtual ~Camera() {};
	void setParent(const Game* game_parent);
	void setName(const sf::String &name);
	void setView(sf::View *view);
	void setSpeed(const float& movement_speed);
	virtual void moveView(const sf::Vector2f& position);
	
	// Virtual functions that don't exist in base class
	virtual Camera* type() = 0;
	virtual void controller() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	const Game* getParent() const;
	sf::String getName() const;
	float getSpeed() const;
	sf::View* getView();
};

// Create our debug camera
class DebugCamera: public Camera
{
private:
	sf::Font font;
	sf::Text text_interface;
	sf::Vector2f position_offset = sf::Vector2f(0.0f, 0.0f);

	bool loadFont(const sf::String& file_location);
	void loadDebugText(const sf::Vector2f& position);
	void setTextPosition(const sf::Vector2f& position);
	void updateDebugText(const sf::Vector2f& position);
public:
	DebugCamera(const sf::String& name, sf::View* view);
	DebugCamera(const sf::String& name, const Game* game_parent, sf::View* view);
	virtual void controller() override;
	virtual void moveView(const sf::Vector2f& position) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual DebugCamera* type() override;
};