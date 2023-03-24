#include "BorderHandler.h"

BorderHandler::~BorderHandler()
{
	Borders.clear();
}

void BorderHandler::createBorder(sf::Vector2f size, sf::Vector2f position, float rotationAngle)
{
	Border* new_border = new Border(size, position, rotationAngle);
	Borders.push_back(new_border);
}

void BorderHandler::checkBorders(Player& player, float deltaTime)
{
	for (auto it = Begin(); it != End(); ++it) {
		(*it)->checkCollision(player, deltaTime);
	}
}

void BorderHandler::Draw(sf::RenderWindow& window)
{
	for (auto it = Begin(); it != End(); ++it) {
		(*it)->Draw(window);
	}
}
