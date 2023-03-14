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
	buttons[0].setPosition(sf::Vector2f(BUTTON_POSITION_X, BUTTON_POSITION_Y * 1 - 40.0f));
	buttons[0].setCharacterSize(MENU_BUTTON_CHAR_SIZE);

	buttons[1].setFont(font);
	buttons[1].setFillColor(sf::Color::White);
	buttons[1].setString("About");
	buttons[1].setPosition(sf::Vector2f(BUTTON_POSITION_X, BUTTON_POSITION_Y * 2 - 40.0f));
	buttons[1].setCharacterSize(MENU_BUTTON_CHAR_SIZE);

	buttons[2].setFont(font);
	buttons[2].setFillColor(sf::Color::White);
	buttons[2].setString("Exit");
	buttons[2].setPosition(sf::Vector2f(BUTTON_POSITION_X, BUTTON_POSITION_Y * 3 - 40.0f));
	buttons[2].setCharacterSize(MENU_BUTTON_CHAR_SIZE);
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(MenuBackgroundSprite);
	for (int i = 0; i < MENU_BUTTONS_AMOUNT; i++) {
		window.draw(buttons[i]);
	}
}

void Menu::Move(bool isDown)
{
	// up
	if (!isDown && buttonIndex > PlayButton) {
		buttons[buttonIndex].setFillColor(sf::Color::White);
		buttons[buttonIndex - 1].setFillColor(sf::Color::Red);
		buttonIndex--;
	}
	// down
	if (isDown && buttonIndex < ExitButton) {
		buttons[buttonIndex].setFillColor(sf::Color::White);
		buttons[buttonIndex + 1].setFillColor(sf::Color::Red);
		buttonIndex++;
	}
}

