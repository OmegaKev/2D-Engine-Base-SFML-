#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::Clock clock;
public:
	sf::Clock& getClock();
};