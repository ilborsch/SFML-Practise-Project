#include "NPC.h"
#include "DEFINITIONS.hpp"

NPC::NPC(sf::Texture* texture, sf::Font& message_font, sf::Vector2f size, sf::Keyboard::Key key, sf::Vector2u imageCount, float switchTime, float cooldown)
	: animation(texture, imageCount, switchTime)
{
	body.setTexture(texture);
	body.setSize(size);
	body.setPosition(sf::Vector2f(NPC_PORTAL_POS_X, NPC_PORTAL_POS_Y));
	
	sf::Texture speechTexture;
	speechTexture.loadFromFile(SPEECH_TEXTURE_PATH);
	speech.setTexture(&speechTexture);
	speech.setSize(sf::Vector2f(SPEECH_SIZE_X, SPEECH_SIZE_Y));
	speech.setPosition(body.getPosition().x - 100, body.getPosition().y - 50);

	NPC_message.setFont(message_font);
	NPC_message.setString("Keep going.");
	NPC_message.setCharacterSize(10.0f);
	NPC_message.setPosition(speech.getPosition());

	this->NPC_message = NPC_message;
	this->key = key;
	this->cooldown = cooldown;
	this->timeLeftToRefresh = cooldown;
	this->pressed = false;
	
	sound_buffer.loadFromFile(NPC_PORTAL_SOUND_PATH);
	speak_Sound.setBuffer(sound_buffer);
	speak_Sound.setVolume(NPC_PORTAL_SOUND_VOLUME);
}

void NPC::Update(float deltaTime, sf::RenderWindow& window, sf::FloatRect playerBounds)
{
	animation.Update(0, deltaTime, false);
	body.setTextureRect(animation.textureRect);
	if (sf::Keyboard::isKeyPressed(key)) {
		if (!pressed) {
			speak_Sound.play();
			pressed = true;
		}
		else if (timeLeftToRefresh <= 0.0f) {
			timeLeftToRefresh = cooldown;
			pressed = false;
		}
	}
	if (pressed && body.getGlobalBounds().intersects(playerBounds)) {
		window.draw(speech);
		window.draw(NPC_message);
	}
	timeLeftToRefresh -= deltaTime;
}

void NPC::Draw(sf::RenderWindow& window)
{
	window.draw(body);

}
