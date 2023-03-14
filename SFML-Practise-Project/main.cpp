#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "ResourceBar.h"
#include "Menu.h"
#include "DEFINITIONS.hpp"


void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME, sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(FRAME_RATE_LIMIT);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(float(VIEW_WIDTH), float(VIEW_HEIGHT)));

	sf::Texture playerTexture, background, staminaTexture;
	playerTexture.loadFromFile(PLAYER_TEXTURE_PATH);
	background.loadFromFile(BACKGROUND_TEXTURE_PATH);
	staminaTexture.loadFromFile(STAMINA_TEXTURE_PATH);
	sf::Sprite backgroundSprite(background);

	Menu menu;
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
					return EXIT_SUCCESS;
				case event.Resized:
					std::cout << event.size.width << " " << event.size.height << std::endl;
					ResizeView(window, view);
					break;				
			}
		}

		window.clear();
		if (menu.IsOpened()) {
			switch (event.type) {
				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::W || sf::Event::KeyReleased == sf::Keyboard::Up)
						menu.Move(false);
					else if (event.key.code == sf::Keyboard::S || sf::Event::KeyReleased == sf::Keyboard::Down)
						menu.Move(true);
					break;
			}
			menu.Draw(window);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				switch (menu.getButtonIndex()) {
					case menu.PlayButton:
						menu.setMenuState(false);
						break;
					case menu.AboutButton:
						std::cout << "Have not done yet ;(" << std::endl;
						break;
					case menu.ExitButton:
						window.close();
						return EXIT_SUCCESS;
				}
			}
		}
		else {
			player.Update(deltaTime);
			view.setCenter(player.getPosition());
			window.setView(view);
			window.draw(backgroundSprite);
			player.Draw(window);
		}
		window.display();
	}
	return EXIT_SUCCESS;
}