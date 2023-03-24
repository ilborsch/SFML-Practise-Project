#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "ResourceBar.h"
#include "Menu.h"
#include "Border.h"
#include "BorderHandler.h"
#include "DEFINITIONS.hpp"
#include "NPC.h"
#include "NPCHandler.h"

static unsigned int LEVEL = 1;

void GenerateBorders_1(BorderHandler& borders) {
	borders.createBorder(sf::Vector2f(30.0f, WINDOW_HEIGHT), sf::Vector2f(360, 0), 0.0f);
	borders.createBorder(sf::Vector2f(1850, 30.0f), sf::Vector2f(300, 560), 359.7f);
	borders.createBorder(sf::Vector2f(300, 30.0f), sf::Vector2f(2150, 460), 9.0f);
	borders.createBorder(sf::Vector2f(900, 30.0f), sf::Vector2f(2450, 500), 0.0f);
	borders.createBorder(sf::Vector2f(30.0f, WINDOW_HEIGHT), sf::Vector2f(3133, 0), 0.0f);
	borders.createBorder(sf::Vector2f(30.0f, 100.0f), sf::Vector2f(3100, 600), 0.0f);
	borders.createBorder(sf::Vector2f(385, 30.0f), sf::Vector2f(300, 775), 0.0f);
	borders.createBorder(sf::Vector2f(100, 30.0f), sf::Vector2f(715, 800), 0.0f);
	borders.createBorder(sf::Vector2f(350, 35.0f), sf::Vector2f(833, 825), 0.0f);
	borders.createBorder(sf::Vector2f(1000, 35.0f), sf::Vector2f(1190, 845), 0.0f);
	borders.createBorder(sf::Vector2f(2.0f, 15.0f), sf::Vector2f(2230.0f, 815.0f), 0.0f);
	borders.createBorder(sf::Vector2f(35.0f, 35.0f), sf::Vector2f(2230.0f, 845.0f), 0.0f);
	borders.createBorder(sf::Vector2f(650.0f, 35.0f), sf::Vector2f(2310.0f, 885.0f), 0.0f);
	borders.createBorder(sf::Vector2f(200.0f, 35.0f), sf::Vector2f(3000.0f, 850.0f), 0.0f);
	borders.createBorder(sf::Vector2f(10.0f, 10.0f), sf::Vector2f(3000.0f, 842.0f), 0.0f);
}

void GenerateBorders_2(BorderHandler& borders) {
}


void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}