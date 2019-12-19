#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "Water");
	loadTextures();
	
}

DrawSystem::~DrawSystem(){}

void DrawSystem::drawScene() {
	System& sys = *system;
	w = window->getSize().x;
	h = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0, 0, w, h)));

	
}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::draw(std::string s) {
	System& sys = *system;
	window->clear();
	w = window->getSize().x;
	h = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0, 0, w, h)));

	std::stringstream ss;
	ss << s;
	std::string comm;
	while (ss >> comm) {
		if (comm == "OBJ") {
			std::string name;
			int type;
			Vector2d pos;
			Color col; col.a = 255;
			int hp, points;
			ss >> name;
			ss >> type;
			ss >> pos.x >> pos.y;
			ss >> col.r >> col.g >> col.b;
			ss >> hp >> points;
			
			if (type == 0) {
				fillCircle(pos.x, pos.y, 5, col);
				text(std::to_string(hp), pos.x, pos.y-15, 20, col);
			}
			else {
				fillCircle(pos.x, pos.y, 5, col);
				fillCircle(pos.x, pos.y, 4, {0, 0, 0});
			}


		}
	}

}
