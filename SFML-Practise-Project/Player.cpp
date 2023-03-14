#include "Player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceBar.h"
#include <SFML/Audio.hpp>
#include "DEFINITIONS.hpp"

Player::Player(sf::Texture* textureA, sf::Vector2f playerSize, sf::Vector2u imageCountA, float switchTime, float velocity, sf::Texture* textureB, sf::Vector2f barSize, sf::Vector2u imageCountB)
	: animation(textureA, imageCountA, switchTime), staminaBar(textureB, barSize, imageCountB) {
	this->velocity = velocity;
	row = 0;
	faceRight = true;
	stepSoundBuffer.loadFromFile(STEP_SOUND_PATH);
	stepSound.setBuffer(stepSoundBuffer);
	stepSound.setVolume(STEP_SOUND_VOLUME);
	sf::Vector2f playerPos(PLAYER_POS_X, PLAYER_POS_Y);
	body.setSize(playerSize);
	body.setOrigin(playerSize.x / 2, playerSize.y / 2);
	body.setPosition(playerPos);
	staminaBar.SetPosition(sf::Vector2f(playerPos.x - STAMINA_BAR_DISTANCE_X, playerPos.y - STAMINA_BAR_DISTANCE_Y));
	body.setTexture(textureA);
}

void Player::Update(float deltaTime) {
	sf::Vector2f movement;
	staminaBar.Update(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= velocity * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += velocity * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += velocity * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= velocity * deltaTime;

	if (!movement.x && !movement.y) {
		row = 5;
		animation.Update(row, 0U);
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && !staminaBar.BarIsBlank()) {
			animation.setAnimationDelay(SPRINT_ANIMATION_DELAY);
			movement.x *= SPRINT_VELOCITY_SCALE, movement.y *= SPRINT_VELOCITY_SCALE;
			row = 2;
		}
		else {
			row = 1;
			animation.setAnimationDelay(WALK_ANIMATION_DELAY);
		}
		if (!movement.y) faceRight = movement.x > 0;
		animation.Update(row, deltaTime, faceRight);
	}
	body.setTextureRect(animation.textureRect);
	Move(movement);
	if (animation.getColumn() == 1 || animation.getColumn() == 5) {
		stepSound.play();
	}
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(body);
	staminaBar.Draw(window);
}

sf::Vector2f Player::getPosition() {
	return body.getPosition();
}

void Player::Move(sf::Vector2f movement) {
	body.move(movement);
	staminaBar.Move(movement);
}
