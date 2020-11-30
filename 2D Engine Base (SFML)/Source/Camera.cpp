#include "Camera.h"

Camera::Camera(const sf::String& name, const Game* game_parent, sf::View* view)
{
	this->setParent(game_parent);
	this->setName(name);
	this->setView(view);
}

Camera::Camera(const sf::String& name, sf::View* view) : Camera(name, NULL, view){}

void Camera::setParent(const Game* game_parent)
{
	this->game_parent = game_parent;
}

void Camera::setName(const sf::String& name)
{
	this->name = name;
}

void Camera::setView(sf::View* view)
{
	this->view = view;
}

void Camera::setSpeed(const float& movement_speed)
{
	this->speed = movement_speed;
}

void Camera::moveView(const sf::Vector2f& position)
{
	// TODO: Add constraints to movement
	this->view->move(position);
}

const Game* Camera::getParent() const
{
	return this->game_parent;
}

sf::String Camera::getName() const
{
	return this->name;
}

float Camera::getSpeed() const
{
	return this->speed;
}

sf::View* Camera::getView()
{
	return this->view;
}

DebugCamera::DebugCamera(const sf::String& name, const Game* game_parent, sf::View* view) : Camera(name, game_parent, view)
{
	// Load the debug camera text at 0,0
	this->loadDebugText(this->position_offset);
}

DebugCamera::DebugCamera(const sf::String& name, sf::View* view) : DebugCamera(name, NULL, view) {}

bool DebugCamera::loadFont(const sf::String& file_location)
{
	if (!this->font.loadFromFile(file_location))
	{
		std::cout << "Failed to load Font file: [" + file_location.toAnsiString() + "]." << std::endl;
		return false;
	}

	return true;
}

void DebugCamera::setTextPosition(const sf::Vector2f& position)
{
	this->text_interface.setPosition(position);
}

void DebugCamera::updateDebugText(const sf::Vector2f& position)
{
	sf::String str = sf::String(sf::String(this->getName() + "\n"
		+ "Camera Position: " + std::to_string((int)position.x) + "," + std::to_string((int)position.y)));

	this->text_interface.setString(str);
	this->setPosition(position);
}

// Controls the debug camera and moves the view attached to it
void DebugCamera::controller()
{
	float speed = this->getSpeed();
	sf::Vector2f mv = sf::Vector2f();

	// Vertical movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))mv += sf::Vector2f(0.0f, -1.0f * speed);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))mv += sf::Vector2f(0.0f, 1.0f * speed);

	// Horizontal movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))mv += sf::Vector2f(-1.0f * speed, 0.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))mv += sf::Vector2f(1.0f * speed, 0.0f);

	if (mv.x != 0.0f || mv.y != 0.0f)this->moveView(mv);
}

void DebugCamera::moveView(const sf::Vector2f& position)
{
	Camera::moveView(position);
	
	sf::Vector2f pos = this->getView()->getCenter() - (this->getView()->getSize() / 2.0f);
	this->updateDebugText(pos + this->position_offset);
}

void DebugCamera::loadDebugText(const sf::Vector2f& position)
{
	// Load this font into memory
	if (!this->loadFont("Font/Roboto-Regular.ttf"))return;

	this->text_interface.setFont(this->font);
	this->text_interface.setFillColor(sf::Color::Red);
	this->text_interface.setCharacterSize(16);
	this->updateDebugText(position);
}

void DebugCamera::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transformations
	states.transform *= getTransform();

	// Draw Debug Camera text
	target.draw(this->text_interface, states);
}

DebugCamera* DebugCamera::type()
{
	return this;
}