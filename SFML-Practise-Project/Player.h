#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2f playerSize, sf::Vector2u imageCount, float switchTime, float velocity);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();

private:
	sf::RectangleShape body;
	Animation animation;
	float velocity;
	unsigned int row;
	unsigned int maxColumn;
	bool faceRight;

};

