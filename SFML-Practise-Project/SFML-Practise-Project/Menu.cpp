#include "Menu.h"
#include "DEFINITIONS.hpp"

Menu::Menu()
{
	font.loadFromFile(MENU_FONT_PATH);
	menu_texture.loadFromFile(MENU_BACKGROUND_TEXTURE_PATH);
	MenuBackgroundSprite.setTexture(menu_texture);
	buttonIndex = 0;
	isOpened = true;

	buttons[0].setFont(font);
	buttons[0].setFillColor(sf::Color::Red);
	buttons[0].setString("Play");
	buttons[0].setPosition(sf::Vector2f(BUTTON_POSITION_X, BUTTON_POSITION_Y * 1 - 80.0f));
	buttons[0].setCharacterSize(MENU_BUTTON_CHAR_SIZE);
	buttons[0].setOutlineColor(sf::Color::Black);
	buttons[0].setOutlineThickness(MENU_BUTTON_THICKNESS);

	buttons[1].setFont(font);
	buttons[1].setFillColor(sf::Color::White);
	buttons[1].setString("About");
	buttons[1].setPosition(sf::Vector2f(BUTTON_POSITION_X, BUTTON_POSITION_Y * 2 - 80.0f));
	buttons[1].setCharacterSize(MENU_BUTTON_CHAR_SIZE);
	buttons[1].setOutlineColor(sf::Color::Black);
	buttons[1].setOutlineThickness(MENU_BUTTON_THICKNESS);

	buttons[2].setFont(font);
	buttons[2].setFillColor(sf::Color::White);
	buttons[2].setString("Exit");
	buttons[2].setPosition(sf::Vector2f(BUTTON_POSITION_X, BUTTON_POSITION_Y * 3 - 80.0f));
	buttons[2].setCharacterSize(MENU_BUTTON_CHAR_SIZE);
	buttons[2].setOutlineColor(sf::Color::Black);
	buttons[2].setOutlineThickness(MENU_BUTTON_THICKNESS);
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(MenuBackgroundSprite);
	for (int i = 0; i < MENU_BUTTONS_AMOUNT; i++) {
		window.draw(buttons[i]);
	}
}

void Menu::Move(float deltaTime)
{
	timeToNewSwitch = std::max(0.0f, timeToNewSwitch - deltaTime);

	if (timeToNewSwitch == 0.0f) {
		// up
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && buttonIndex > PlayButton) {
			buttons[buttonIndex].setFillColor(sf::Color::White);
			buttons[buttonIndex - 1].setFillColor(sf::Color::Red);
			buttonIndex--;
		}
		// down
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && buttonIndex < ExitButton) {
			buttons[buttonIndex].setFillColor(sf::Color::White);
			buttons[buttonIndex + 1].setFillColor(sf::Color::Red);
			buttonIndex++;
		}
		timeToNewSwitch = switchTime;
	}
}

