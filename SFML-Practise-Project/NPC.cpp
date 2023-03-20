#include "NPC.h"
#include "DEFINITIONS.hpp"

NPC::NPC(sf::Texture* texture, sf::Font& interact_font, sf::Vector2f size, sf::Vector2u imageCount, float switchTime)
	: animation(texture, imageCount, switchTime)
{
	body.setTexture(texture);
	body.setSize(size);
	body.setPosition(sf::Vector2f(NPC_PORTAL_POS_X, NPC_PORTAL_POS_Y));
	
	speechTexture.loadFromFile(SPEECH_TEXTURE_PATH);
	speech.setTexture(&speechTexture);
	speech.setSize(sf::Vector2f(SPEECH_TEXTURE_SIZE_X * 2.1, SPEECH_SIZE_Y * 2.1));
	speech.setPosition(body.getPosition().x + 7.0f, body.getPosition().y - 108.0f);
	npc_message_font.loadFromFile(NPC_FONT_PATH);

	NPC_message.setFont(npc_message_font);
	NPC_message.setString("KEEP GOING.");
	NPC_message.setCharacterSize(35.0f);
	NPC_message.setPosition(speech.getPosition().x + 51.0f, speech.getPosition().y + 43.5f);
	NPC_message.setFillColor(sf::Color::Black);

	interact_message.setFont(interact_font);
	interact_message.setString("Press [ F ] to interact.");
	interact_message.setCharacterSize(15.5f);
	interact_message.setPosition(body.getPosition().x - 22.0f, body.getPosition().y + 128.0f);
	interact_message.setOutlineColor(sf::Color::White);
	interact_message.setOutlineThickness(1.7f);
	interact_message.setFillColor(sf::Color::Black);

	this->NPC_message = NPC_message;
	this->pressed = false;
	
	sound_buffer.loadFromFile(NPC_PORTAL_SOUND_PATH);
	speak_Sound.setBuffer(sound_buffer);
	speak_Sound.setVolume(NPC_PORTAL_SOUND_VOLUME);
}

void NPC::Update(float deltaTime, sf::RenderWindow& window, sf::FloatRect playerBounds)
{
	animation.Update(0, deltaTime, false);
	body.setTextureRect(animation.textureRect);
	window.draw(body);

	if (!pressed && intersects(playerBounds) && sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		pressed = true;
		speak_Sound.play();
	}
	else if (!intersects(playerBounds))
		pressed = false;


	if (pressed) {
		window.draw(speech);
		window.draw(NPC_message);
	}
	else if (intersects(playerBounds))
		window.draw(interact_message);
}

bool NPC::intersects(sf::FloatRect playerBounds)
{
	playerBounds.left -= NPC_INTERACT_AREA;
	playerBounds.top -= NPC_INTERACT_AREA;
	playerBounds.width += NPC_INTERACT_AREA * 2;
	playerBounds.height += NPC_INTERACT_AREA * 2;

	return playerBounds.intersects(body.getGlobalBounds());
}
