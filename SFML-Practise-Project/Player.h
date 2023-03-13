#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "ResourceBar.h"
#include <SFML/Audio.hpp>

class Player
{
public:
	Player(sf::Texture* textureA, sf::Vector2f playerSize, sf::Vector2u imageCountA, float switchTime, float velocity, sf::Texture* textureB, sf::Vector2f barSize, sf::Vector2u imageCountB);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	void Move(sf::Vector2f movement);
private:
	sf::RectangleShape body;
	ResourceBar staminaBar;
	Animation animation;
	sf::Sound stepSound;
	sf::SoundBuffer stepSoundBuffer;
	float velocity;
	unsigned int row;
	unsigned int maxColumn;
	bool faceRight;

};

