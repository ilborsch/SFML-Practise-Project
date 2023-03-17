#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "ResourceBar.h"
#include "Menu.h"
#include "Border.h"
#include "BorderHandler.h"
#include "DEFINITIONS.hpp"



void GenerateBorders(BorderHandler& borders) {
	borders.createBorder(sf::Vector2f(30.0f, WINDOW_HEIGHT), sf::Vector2f(360, 0), 0.0f);
	borders.createBorder(sf::Vector2f(1850, 30.0f), sf::Vector2f(300, 560), 359.7f);
	borders.createBorder(sf::Vector2f(300, 30.0f), sf::Vector2f(2150, 460), 9.0f);
	borders.createBorder(sf::Vector2f(900, 30.0f), sf::Vector2f(2450, 500), 0.0f);
	borders.createBorder(sf::Vector2f(30.0f, WINDOW_HEIGHT), sf::Vector2f(3133, 0), 0.0f);
	borders.createBorder(sf::Vector2f(30.0f, 100.0f), sf::Vector2f(3100, 600), 0.0f);
	borders.createBorder(sf::Vector2f(385, 30.0f), sf::Vector2f(300, 775), 0.0f);
	borders.createBorder(sf::Vector2f(100, 30.0f), sf::Vector2f(715, 800), 0.0f);
	borders.createBorder(sf::Vector2f(350, 35.0f), sf::Vector2f(833, 825), 0.0f);
	borders.createBorder(sf::Vector2f(1000, 35.0f), sf::Vector2f(1190, 845), 0.0f);
	borders.createBorder(sf::Vector2f(2.0f, 15.0f), sf::Vector2f(2230.0f, 815.0f), 0.0f);
	borders.createBorder(sf::Vector2f(35.0f, 35.0f), sf::Vector2f(2230.0f, 845.0f), 0.0f);
	borders.createBorder(sf::Vector2f(650.0f, 35.0f), sf::Vector2f(2310.0f, 885.0f), 0.0f);
	borders.createBorder(sf::Vector2f(200.0f, 35.0f), sf::Vector2f(3000.0f, 850.0f), 0.0f);
	borders.createBorder(sf::Vector2f(10.0f, 10.0f), sf::Vector2f(3000.0f, 842.0f), 0.0f);
}


void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME, sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(FRAME_RATE_LIMIT);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(float(VIEW_WIDTH), float(VIEW_HEIGHT))), main_menu_view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(float(MAIN_MENU_VIEW_WIDTH), float(MAIN_MENU_VIEW_HEIGHT)));

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

	BorderHandler borders;
	GenerateBorders(borders);
	Border PortalActivationArea(sf::Vector2f(PORTAL_SIZE, PORTAL_SIZE), sf::Vector2f(PORTAL_POSITION_X, PORTAL_POSITION_Y), 0.0f);
	sf::Text PortalActivationText;
	sf::Font PortalActivationFont;
	PortalActivationFont.loadFromFile(PORTAL_FONT_PATH);
	PortalActivationText.setFont(PortalActivationFont);
	PortalActivationText.setString("Press [Enter] to continue your path...");
	PortalActivationText.setFillColor(sf::Color::Black);
	PortalActivationText.setPosition(PORTAL_TEXT_POSITION_X, PORTAL_TEXT_POSITION_Y);
	PortalActivationText.setCharacterSize(16.0f);

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
		if (!menu.IsOpened() && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			menu.changeMenuState();
		window.clear();
		if (menu.IsOpened()) {
			menu.Move(deltaTime);
			menu.Draw(window);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				switch (menu.getButtonIndex()) {
					case menu.PlayButton:
						menu.changeMenuState();
						break;
					case menu.AboutButton:
						std::cout << "Have not done yet ;(" << std::endl;
						break;
					case menu.ExitButton:
						window.close();
						return EXIT_SUCCESS;
				}
			}
			main_menu_view.setCenter(MAIN_MENU_VIEW_WIDTH / 2, MAIN_MENU_VIEW_HEIGHT / 2);
			window.setView(main_menu_view);
		}
		else {
			player.Update(deltaTime);
			borders.checkBorders(player, deltaTime);
			view.setCenter(player.getPosition());
			window.setView(view);
			window.draw(backgroundSprite);
			if (PortalActivationArea.isCollide(player)) {
				window.draw(PortalActivationText);
			}
			player.Draw(window);
		}
		window.display();
	}
	return EXIT_SUCCESS;
}