#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Animation.h"
#include <SFML/Audio.hpp>

class NPC
{
public:
	NPC(sf::Texture* texture, sf::Font& interact_font, sf::Font& npc_message_font, sf::SoundBuffer& sound_buffer, sf::Texture& speechTexture, sf::Vector2f size, sf::Vector2u imageCount, sf::Vector2f pos, float switchTime);
	void Update(float deltaTime, sf::RenderWindow& window, sf::FloatRect playerBounds);

private:
	bool intersects(sf::FloatRect playerBounds);
	bool pressed;

	sf::RectangleShape body;
	sf::Texture speechTexture;
	sf::Font npc_message_font;
	sf::RectangleShape speech;
	sf::Text NPC_message, interact_message;
	sf::SoundBuffer sound_buffer;
	sf::Sound speak_Sound;

	Animation animation;
};

