#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"

class Animation {
public:
	sf::IntRect textureRect;
	unsigned int Y = 0;

	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	void Update(unsigned int row, float deltaTime, bool faceRight, int minColumn = NO_VALUE, int maxColumn = NO_VALUE);
	void Update(unsigned int row, unsigned int column);
	inline unsigned int getColumn() { return currentImage.x; }
	inline unsigned int getRow() { return currentImage.y; }
	void setAnimationDelay(float delay) { animationDelay = delay; }
private:
	sf::Vector2u imageCount; 
	sf::Vector2u currentImage; 
	float animationDelay;
	float totalTime; 
};

