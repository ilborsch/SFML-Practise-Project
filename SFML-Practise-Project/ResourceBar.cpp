#include "ResourceBar.h"
#include "DEFINITIONS.hpp"

ResourceBar::ResourceBar(sf::Texture* texture, sf::Vector2f barSize, sf::Vector2u imageCount)
	: animation(texture, imageCount, 0.0f)
{
	isBlank = false;
	column = 0;
	timeToResourceEnding = TIME_TO_RESOURCE_ENDING;
	columnStages = imageCount.x;
	bar.setSize(barSize);
	bar.setOrigin(barSize.x / 2, barSize.y / 2);
	bar.setTexture(texture);
}

void ResourceBar::Draw(sf::RenderWindow& window) {
	window.draw(bar);
}

void ResourceBar::Update(float deltaTime) {
	if (!isBlank) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
			timeToResourceEnding = std::max(timeToResourceEnding - deltaTime, 0.0f);
		}
		else animation.Update(0U, column);
		if (!timeToResourceEnding) {
			animation.Update(0U, column);
			isBlank = true;
			column = 0;
		}
		if (timeToResourceEnding == TIME_TO_RESOURCE_ENDING) {
			column = 0;
			animation.Update(0U, column);
		}
		else {
			column = columnStages - (unsigned int)trunc(timeToResourceEnding) - 2;
			animation.Update(0U, column);
		}

	}
	else {
		if (timeToResourceEnding == TIME_TO_RESOURCE_ENDING * 2) {
			timeToResourceEnding /= 2;
			isBlank = false;
			column = 0;
		}
		else {
			timeToResourceEnding = std::min(timeToResourceEnding + deltaTime, TIME_TO_RESOURCE_ENDING * 2);
			column = (unsigned int)trunc(timeToResourceEnding / 2);
			animation.Update(1U, column);
		}
	}
	bar.setTextureRect(animation.textureRect);
}

void ResourceBar::Move(sf::Vector2f movement) {
	bar.move(movement);
}

void ResourceBar::SetPosition(sf::Vector2f barPosition)
{
	bar.setPosition(barPosition);
}
