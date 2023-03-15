#include "BorderHandler.h"

void BorderHandler::createBorder(sf::Vector2f size, sf::Vector2f position, float rotationAngle)
{
	Border new_border(size, position, rotationAngle);
	Borders.push_back(new_border);
}

void BorderHandler::checkBorders(Player& player, float deltaTime)
{
	for (auto it = Begin(); it != End(); ++it) {
		it->checkCollision(player, deltaTime);
	}
}
