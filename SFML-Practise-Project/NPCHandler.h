#pragma once
#include "NPC.h"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include <SFML/Audio.hpp>
#include <vector>

class NPCHandler
{
public:
	~NPCHandler();
	void Create_NPC(sf::Texture* texture, sf::Font& interact_font, sf::Font& npc_message_font, sf::SoundBuffer& sound_buffer, sf::Texture& speechTexture, sf::Vector2f size, sf::Vector2u imageCount, sf::Vector2f pos, float switchTime);
	void Update(float deltaTime, sf::RenderWindow& window, sf::FloatRect playerBounds);
	void Clear() { NPCharacters.clear(); }
private:
	std::vector<NPC*> NPCharacters;
	inline std::vector<NPC*>::iterator Begin() { return NPCharacters.begin(); }
	inline std::vector<NPC*>::iterator End() { return NPCharacters.end(); }
};

