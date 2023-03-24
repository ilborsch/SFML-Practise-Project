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
	void Move(sf::Vector2f movement);
	void Move(float x, float y);
	inline sf::Vector2f getPosition() { return body.getPosition(); }
	inline sf::FloatRect getGlobalBounds() { return body.getGlobalBounds(); }
	inline sf::Vector2f getMovement() { return movement; }
private:
	sf::RectangleShape body;
	ResourceBar staminaBar;
	Animation animation;
	sf::Sound stepSound;
	sf::SoundBuffer stepSoundBuffer;
	sf::Vector2f movement;
	float velocity;
	unsigned int row;
	unsigned int maxColumn;
	bool faceRight;

};

