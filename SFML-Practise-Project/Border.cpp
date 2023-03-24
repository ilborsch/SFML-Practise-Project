#include "Border.h"

Border::Border(sf::Vector2f size, sf::Vector2f position, float rotationAngle)
{
	body.setSize(size);
	body.setRotation(rotationAngle);
	body.setPosition(position);
}

bool Border::isCollide(Player& player)
{
	return body.getGlobalBounds().intersects(player.getGlobalBounds());
}

void Border::checkCollision(Player& player, float deltaTime)
{
	sf::Vector2f player_movement = player.getMovement();
	sf::Vector2f movement = sf::Vector2f(-player_movement.x, -player_movement.y);
	if (isCollide(player)) {
		player.Move(movement);
	}
}


void Border::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}