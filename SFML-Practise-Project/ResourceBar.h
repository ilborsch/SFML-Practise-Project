#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class ResourceBar
{
public:
	ResourceBar(sf::Texture* texture, sf::Vector2f barSize, sf::Vector2u imageCount, float switchTime);
	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
private:
	Animation animation;
	sf::RectangleShape bar;
	bool isBlank;
	unsigned int column, columnStages;
	float timeToResourceEnding;
};

