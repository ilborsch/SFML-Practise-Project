#pragma once
#include "Border.h"
#include "Player.h"
#include "DEFINITIONS.hpp"
#include <vector>

class BorderHandler
{
public:
	void createBorder(sf::Vector2f size, sf::Vector2f position, float rotationAngle);
	void checkBorders(Player& player, float deltaTime);
	void Draw(sf::RenderWindow& window);
private:
	std::vector<Border> Borders;
	inline std::vector<Border>::iterator Begin() { return Borders.begin(); }
	inline std::vector<Border>::iterator End() { return Borders.end(); }
};

