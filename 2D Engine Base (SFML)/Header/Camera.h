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
	sf::View* master_view;									// View from which properties are pulled
	std::vector<std::shared_ptr<sf::View>> view_list;		// Attach 1 or more camera's to this view
	float speed = 3.0f;
public:
	Camera(const sf::String& name, const sf::View &view);
	Camera(const sf::String& name, const Game* game_parent, const sf::View &view);
	virtual ~Camera() {};
	void addView();
	void addView(const sf::View &view);
	void setMasterView(sf::View* view);
	void setParent(const Game* game_parent);
	void setName(const sf::String &name);
	void setSpeed(const float& movement_speed);			// TODO: Refactor
	virtual void moveView(const sf::Vector2f& position);
	
	// Virtual functions that don't exist in base class
	virtual Camera* type() = 0;
	virtual void controller() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	const Game* getParent() const;			// Return the game parent
	sf::String getName() const;				// Return the name of this camera
	float getSpeed() const;					// Return the speed of this camera
	sf::View* getView(int v_index);			// Return the view by index
	size_t getNumViews() const;			// Returns number of Views attached to camera
};

// Create our debug camera
class DebugCamera: public Camera
{
private:
	sf::Font font;
	sf::Text text_interface;
	sf::View text_view;			// A view for the debug text

	bool loadFont(const sf::String& file_location);
	void loadDebugText();
	void setTextPosition(const sf::Vector2f& position);
	void updateDebugText();
public:
	DebugCamera(const sf::String& name, const sf::View &view);
	DebugCamera(const sf::String& name, const Game* game_parent, const sf::View &view);
	virtual void controller() override;
	virtual void moveView(const sf::Vector2f& position) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual DebugCamera* type() override;
};