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
#include "NPC.h"
#include "NPCHandler.h"
#include "Global.hpp"

int main() {

	sf::Texture playerTexture, background1, background2, staminaTexture, portal_dudeTexture, speechTexture, magicianTexture;
	sf::Font PortalActivationFont, portalDude_message_font;
	sf::SoundBuffer npc_portal_sound_buffer, npc_magician_sound_buffer;

	speechTexture.loadFromFile(SPEECH_TEXTURE_PATH);
	npc_portal_sound_buffer.loadFromFile(NPC_PORTAL_SOUND_PATH);
	npc_magician_sound_buffer.loadFromFile(NPC_MAGICIAN_SOUND_PATH);
	portalDude_message_font.loadFromFile(NPC_FONT_PATH);
	PortalActivationFont.loadFromFile(PORTAL_FONT_PATH);
	playerTexture.loadFromFile(PLAYER_TEXTURE_PATH);
	background1.loadFromFile(BACKGROUND1_TEXTURE_PATH);
	background2.loadFromFile(BACKGROUND2_TEXTURE_PATH);
	staminaTexture.loadFromFile(STAMINA_TEXTURE_PATH);
	portal_dudeTexture.loadFromFile(NPC_PORTAL_TEXTURE_PATH);
	magicianTexture.loadFromFile(NPC_MAGICIAN_TEXTURE_PATH);

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME, sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(float(VIEW_WIDTH), float(VIEW_HEIGHT))), main_menu_view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(float(MAIN_MENU_VIEW_WIDTH), float(MAIN_MENU_VIEW_HEIGHT)));
	sf::Sprite backgroundSprite;
	sf::Text PortalActivationText;
	sf::Clock clock;
	sf::Music music;
	BorderHandler borders;
	Border PortalActivationArea(sf::Vector2f(PORTAL_SIZE, PORTAL_SIZE), sf::Vector2f(PORTAL_POSITION_X, PORTAL_POSITION_Y), 0.0f);
	Menu menu;
	Player player(&playerTexture, sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE), sf::Vector2u(8, 11), WALK_ANIMATION_DELAY, PLAYER_VELOCITY, &staminaTexture, sf::Vector2f(STAMINA_BAR_WIDTH, STAMINA_BAR_HEIGHT), sf::Vector2u(4, 2));
	NPCHandler NPCS;

	music.openFromFile(MUSIC_PATH);
	music.setLoop(true);
	music.play();
	music.setVolume(MUSIC_VOLUME);
	window.setFramerateLimit(FRAME_RATE_LIMIT);
	backgroundSprite.setTexture(background1);

	PortalActivationText.setFont(PortalActivationFont);
	PortalActivationText.setString("Press [Enter] to continue your path...");
	PortalActivationText.setFillColor(sf::Color::Black);
	PortalActivationText.setPosition(PORTAL_TEXT_POSITION_X, PORTAL_TEXT_POSITION_Y);
	PortalActivationText.setCharacterSize(16.0f);
	GenerateBorders_1(borders);
	NPCS.Create_NPC(&portal_dudeTexture, PortalActivationFont, portalDude_message_font, npc_portal_sound_buffer, speechTexture, sf::Vector2f(NPC_PORTAL_SIZE, NPC_PORTAL_SIZE), sf::Vector2u(10, 10), sf::Vector2f(NPC_PORTAL_POS_X, NPC_PORTAL_POS_Y), 0.165f);

	float deltaTime = 0.0f;

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
			NPCS.Update(deltaTime, window, player.getGlobalBounds());
			if (PortalActivationArea.isCollide(player)) {
				window.draw(PortalActivationText);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					switch (LEVEL) {
					case 1:
						backgroundSprite.setTexture(background2);
						NPCS.Clear();
						borders.Clear();
						PortalActivationArea = Border(sf::Vector2f(PORTAL_SIZE, PORTAL_SIZE), sf::Vector2f(PORTAL_POSITION_X, PORTAL_POSITION_Y), 0.0f);
						GenerateBorders_2(borders);
						NPCS.Create_NPC(&magicianTexture, PortalActivationFont, portalDude_message_font, npc_magician_sound_buffer, speechTexture, sf::Vector2f(NPC_MAGICIAN_SIZE, NPC_MAGICIAN_SIZE), sf::Vector2u(4, 3), sf::Vector2f(NPC_MAGICIAN_POS_X, NPC_MAGICIAN_POS_Y), 0.185f);
						player.setPosition(900.0f, 1100.0f);
					}
					LEVEL++;
				}
			}
			player.Draw(window);
		}
		window.display();
	}
	return EXIT_SUCCESS;
}