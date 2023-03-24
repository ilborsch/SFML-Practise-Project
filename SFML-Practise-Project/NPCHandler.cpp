#include "NPCHandler.h"

NPCHandler::~NPCHandler()
{
	NPCharacters.clear();
}

void NPCHandler::Create_NPC(sf::Texture* texture, sf::Font& interact_font, sf::Font& npc_message_font, sf::SoundBuffer& sound_buffer, sf::Texture& speechTexture, sf::Vector2f size, sf::Vector2u imageCount, sf::Vector2f pos, float switchTime)
{
	NPC* newNPC = new NPC(texture, interact_font, npc_message_font, sound_buffer, speechTexture, size, imageCount, pos, switchTime);
	NPCharacters.push_back(newNPC);
}

void NPCHandler::Update(float deltaTime, sf::RenderWindow& window, sf::FloatRect playerBounds)
{
	for (auto it = Begin(); it != End(); ++it) {
		(*it)->Update(deltaTime, window, playerBounds);
	}
}
