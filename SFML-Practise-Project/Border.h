#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "DEFINITIONS.hpp"

class Border
{
public:
	Border(sf::Vector2f size, sf::Vector2f position, float rotationAngle);
	inline sf::Vector2f getPosition() { return body.getPosition(); };
	void checkCollision(Player& player, float deltaTime);
	bool isCollide(Player& player);
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body;
};