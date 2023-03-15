#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"

class Menu
{
public:
	Menu();
	void Draw(sf::RenderWindow& window);
	bool IsOpened() { return isOpened; };
	inline void changeMenuState() { isOpened = !isOpened; }
	inline int getButtonIndex() { return buttonIndex; };
	void Move(float deltaTime);
	enum Buttons {
		PlayButton,
		AboutButton,
		ExitButton
	};
private:
	unsigned int buttonIndex;
	sf::Text buttons[MENU_BUTTONS_AMOUNT];
	sf::Font font;
	sf::Texture menu_texture;
	sf::Sprite MenuBackgroundSprite;
	bool isOpened;
	const float switchTime = 0.33f;
	float timeToNewSwitch = 0.0f;
};

