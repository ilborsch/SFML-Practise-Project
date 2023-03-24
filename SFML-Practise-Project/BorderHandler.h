#pragma once
#include "Border.h"
#include "Player.h"
#include "DEFINITIONS.hpp"
#include <vector>

class BorderHandler
{
public:
	~BorderHandler();
	void createBorder(sf::Vector2f size, sf::Vector2f position, float rotationAngle);
	void checkBorders(Player& player, float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Clear() { Borders.clear(); }
private:
	std::vector<Border*> Borders;
	inline std::vector<Border*>::iterator Begin() { return Borders.begin(); }
	inline std::vector<Border*>::iterator End() { return Borders.end(); }
};

