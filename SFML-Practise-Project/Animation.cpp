#include "Animation.h"
#include <SFML/Graphics.hpp>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->Y = Y;

	totalTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = this->Y;
	textureRect.width = texture->getSize().x / float(imageCount.x);
	textureRect.height = texture->getSize().y / float(imageCount.y);
	setAnimationDelay(switchTime);
}

void Animation::Update(unsigned int row, float deltaTime, bool faceRight, int minColumn, int maxColumn) {
	if (maxColumn == NO_VALUE) maxColumn = imageCount.x;
	if (minColumn == NO_VALUE) minColumn = 0;
	totalTime += deltaTime;
	currentImage.y = row;
	if (totalTime >= animationDelay) {
		totalTime -= animationDelay;
		currentImage.x++;

		if (currentImage.x >= maxColumn)
			currentImage.x = minColumn;
	}
	if (faceRight) {
		textureRect.left = currentImage.x * textureRect.width;
		textureRect.width = abs(textureRect.width);
	}
	else {
		textureRect.left = (currentImage.x + 1) * abs(textureRect.width);
		textureRect.width = -abs(textureRect.width);
	}
	textureRect.top = currentImage.y * textureRect.height;
}

void Animation::Update(unsigned int row, unsigned int column) {
	totalTime = 0;
	currentImage.x = column;
	currentImage.y = row;
	textureRect.width = abs(textureRect.width);
	textureRect.left = textureRect.width * currentImage.x;
	textureRect.top = textureRect.height * currentImage.y;
}