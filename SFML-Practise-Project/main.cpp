#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"

const unsigned int WINDOW_WIDTH = 1366, WINDOW_HEIGHT = 768;
const unsigned int VIEW_WIDTH = 1024, VIEW_HEIGHT = 576;

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Borshch", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);

	//sf::RectangleShape player(sf::Vector2f(130, 130));
	//sf::Vector2f playerPos(640, 360);
	//player.setOrigin(65, 65);
	//player.setPosition(playerPos);
	sf::View view(sf::Vector2f(0.0, 0.0), sf::Vector2f(float(VIEW_WIDTH), float(VIEW_HEIGHT)));
	sf::Texture playerTexture, background;
	playerTexture.loadFromFile("C:/Users/Illia/source/repos/SFML-Practise-Project/Images/tux.png");
	background.loadFromFile("C:/Users/Illia/source/repos/SFML-Practise-Project/Images/background1.jpg");
	sf::Sprite backgroundSprite(background);
	//player.setTexture(&playerTexture);

	//sf::Vector2u textureSize = playerTexture.getSize();
	//textureSize.x /= 8, textureSize.y /= 11;
	//player.setTextureRect(sf::IntRect(0, textureSize.y * 5, textureSize.x, textureSize.y));

	Player player(&playerTexture, sf::Vector2f(170, 170), sf::Vector2u(8, 11), 0.1f, 200.0f);
	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(event)) {
			switch (event.type) {
				case event.Closed:
					window.close();
					break;
				case event.Resized:
					std::cout << event.size.width << " " << event.size.height << std::endl;
					ResizeView(window, view);
					break;

			}
		}
		player.Update(deltaTime);
		view.setCenter(player.getPosition());
		window.clear();
		window.setView(view);
		window.draw(backgroundSprite);
		player.Draw(window);
		window.display();
	}
}