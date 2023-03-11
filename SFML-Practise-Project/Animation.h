#pragma once
#include <SFML/Graphics.hpp>
class Animation {
public:
	sf::IntRect textureRect; // патерн который выводиться на экран
	unsigned int Y = 0;

	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	void Update(unsigned int row, float deltaTime, bool faceRight, int maxColumn = -1, int minColumn = -1);
	void Update(unsigned int row, unsigned int column);

private:
	sf::Vector2u imageCount; // кадр в анимации по счету
	sf::Vector2u currentImage; 

	float totalTime; // время прошедшее с последней смены
	float switchTime; // скорость смены патернов
};

