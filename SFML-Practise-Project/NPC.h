#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Animation.h"
#include <SFML/Audio.hpp>

class NPC
{
public:
	NPC(sf::Texture* texture, sf::Font& message_font, sf::Vector2f size, sf::Keyboard::Key key, sf::Vector2u imageCount, float switchTime, float cooldown);
	void Update(float deltaTime, sf::RenderWindow& window, sf::FloatRect playerBounds);
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body;
	sf::RectangleShape speech;
	sf::Text NPC_message;
	sf::Keyboard::Key key;
	sf::SoundBuffer sound_buffer;
	sf::Sound speak_Sound;
	Animation animation;
	bool pressed;
	float timeLeftToRefresh;
	float cooldown;
};

