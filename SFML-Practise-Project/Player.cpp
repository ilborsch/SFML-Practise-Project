#include "Player.h"
#include <SFML/Graphics.hpp>
#include <string>

Player::Player(sf::Texture* texture, sf::Vector2f playerSize, sf::Vector2u imageCount, float switchTime, float velocity)
	: animation(texture, imageCount, switchTime) {
	this->velocity = velocity;
	row = 0;
	faceRight = true;

	sf::Vector2f playerPos(800, 500);
	body.setSize(playerSize);
	body.setOrigin(playerSize.x / 2, playerSize.y / 2);
	body.setPosition(playerPos);
	body.setTexture(texture);
}

void Player::Update(float deltaTime) {
	sf::Vector2f movement;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= velocity * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += velocity * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += velocity * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= velocity * deltaTime;
	//if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
	//	|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))) {
	//	movement.x = 0.0f;
	//	movement.y = 0.0f;
	//}
	if (!movement.x && !movement.y) {
		row = 5;
		animation.Update(row, 0U);
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
			movement.x *= 1.45, movement.y *= 1.45;
			row = 2;
		}
		else row = 1;
		if (!movement.y) faceRight = movement.x > 0;
		velocity = 100.0f;
		animation.Update(row, deltaTime, faceRight);
	}

	body.setTextureRect(animation.textureRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

sf::Vector2f Player::getPosition() {
	return body.getPosition();
}
