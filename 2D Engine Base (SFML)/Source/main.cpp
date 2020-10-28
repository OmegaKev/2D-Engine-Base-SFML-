#include <SFML/Graphics.hpp>

int main()
{
	// Set window to size 1000, 1000
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML(2.5.1) 2D Engine");

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
		window.display();
	}
	return 0;
}