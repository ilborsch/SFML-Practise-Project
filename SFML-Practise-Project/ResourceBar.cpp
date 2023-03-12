#include "ResourceBar.h"

ResourceBar::ResourceBar(sf::Texture* texture, sf::Vector2f barSize, sf::Vector2u imageCount, float switchTime)
	: animation(texture, imageCount, switchTime)
{
	isBlank = false;
	column = 0;
	timeToResourceEnding = 3.0f;
	columnStages = imageCount.x;

	sf::Vector2f barPos(100, 100);
	bar.setSize(barSize);
	bar.setOrigin(barSize.x / 2, barSize.y / 2);
	bar.setPosition(barPos);
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
		if (timeToResourceEnding == 3.0f) {
			column = 0;
			animation.Update(0U, column);
		}
		else {
			column = columnStages - trunc(timeToResourceEnding) - 2;
			animation.Update(0U, column);
		}

	}
	else {
		if (timeToResourceEnding == 6.0f) {
			timeToResourceEnding /= 2;
			isBlank = false;
			column = 0;
		}
		else {
			timeToResourceEnding = std::min(timeToResourceEnding + deltaTime, 6.0f);
			column = trunc(timeToResourceEnding / 2);
			animation.Update(1U, column);
		}
	}
	bar.setTextureRect(animation.textureRect);
}
