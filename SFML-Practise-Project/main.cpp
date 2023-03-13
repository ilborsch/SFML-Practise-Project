#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "ResourceBar.h"
#include "DEFINITIONS.hpp"


void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME, sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

	//sf::RectangleShape player(sf::Vector2f(130, 130));
	//sf::Vector2f playerPos(640, 360);
	//player.setOrigin(65, 65);
	//player.setPosition(playerPos);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(float(VIEW_WIDTH), float(VIEW_HEIGHT)));
	sf::Texture playerTexture, background, staminaTexture;
	playerTexture.loadFromFile(PLAYER_TEXTURE_PATH);
	background.loadFromFile(BACKGROUND_TEXTURE_PATH);
	staminaTexture.loadFromFile(STAMINA_TEXTURE_PATH);
	sf::Sprite backgroundSprite(background);
	//player.setTexture(&playerTexture);

	//sf::Vector2u textureSize = playerTexture.getSize();
	//textureSize.x /= 8, textureSize.y /= 11;
	// 
	//player.setTextureRect(sf::IntRect(0, textureSize.y * 5, textureSize.x, textureSize.y));
	Player player(&playerTexture, sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE), sf::Vector2u(8, 11), WALK_ANIMATION_DELAY, PLAYER_VELOCITY, &staminaTexture, sf::Vector2f(STAMINA_BAR_WIDTH, STAMINA_BAR_HEIGHT), sf::Vector2u(4, 2));
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Music music;
	music.openFromFile(MUSIC_PATH);
	music.setLoop(true);
	music.play();
	music.setVolume(MUSIC_VOLUME);
	while (window.isOpen()) {
		sf::Event event;
		deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(event)) {
			switch (event.type) {
				case event.Closed:
					window.close();

					break;
				case event.Resized:
					std::cout << event.size.width << " " << event.size.height << std::endl;
					ResizeView(window, view);
					break;
			}
		}
		player.Update(deltaTime);
		view.setCenter(player.getPosition());
		window.clear();
		window.setView(view);
		window.draw(backgroundSprite);
		player.Draw(window);
		window.display();
	}
}