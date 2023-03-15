#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "DEFINITIONS.hpp"

class Border
{
public:
	Border(sf::Vector2f size, sf::Vector2f position, float rotationAngle);
	sf::Vector2f getPosition();
	void checkCollision(Player& player, float deltaTime);
private:
	sf::Vector2f left_top_point, right_bottom_point;
	sf::RectangleShape body;
	float rotationAngle;
	bool isCollide(Player& player);
};