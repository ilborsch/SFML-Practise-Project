#include "Border.h"

Border::Border(sf::Vector2f size, sf::Vector2f position, float rotationAngle)
{
	this->rotationAngle = rotationAngle;
	left_top_point = position;
	right_bottom_point = sf::Vector2f(position.x + size.x, position.y + size.y);
	body.setSize(size);
	body.setRotation(rotationAngle);
}

bool Border::isCollide(Player& player)
{
	return body.getGlobalBounds().intersects(player.getGlobalBounds());
}

sf::Vector2f Border::getPosition()
{
	return sf::Vector2f();
}

void Border::checkCollision(Player& player, float deltaTime)
{
	sf::Vector2f player_movement = player.getMovement();
	sf::Vector2f movement = sf::Vector2f(-player_movement.x, -player_movement.y);
	if (isCollide(player)) {
		player.Move(movement);
	}
}
