#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class ResourceBar
{
public:
	ResourceBar(sf::Texture* texture, sf::Vector2f barSize, sf::Vector2u imageCount);
	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	void Move(sf::Vector2f movement);
	void SetPosition(sf::Vector2f barPosition);
	inline bool BarIsBlank() { return isBlank; }
private:
	bool isBlank;
	Animation animation;
	sf::RectangleShape bar;
	unsigned int column, columnStages;
	float timeToResourceEnding;
};

