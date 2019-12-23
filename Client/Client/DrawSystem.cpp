#include "DrawSystem.h"
#include "random.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "Blinky Pigs");
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

	image("background", 400, 400, 800, 800, 0);

	std::stringstream ss;
	ss << s;
	std::string comm;
	while (ss >> comm) {
		if (comm == "OBJ") {
			std::string name;
			int type;
			Vector2d pos;
			double r;
			Color col; col.a = 255;
			int hp;
			ss >> name;
			ss >> type;
			ss >> pos.x >> pos.y;
			ss >> r;
			ss >> col.r >> col.g >> col.b;
			ss >> hp;
			
			if (type == 0) {
				image("skin", pos.x, pos.y, r*2, r*2, 0, col);
				fillRect(pos.x, pos.y - 12, 31, 5, { 0, 0, 0 });
				for (int i = 0; i < 10; i++) {
					
					if(i < hp)
						fillRect(pos.x - 14 + i * 3, pos.y - 12, 2, 3, col);
					else
						fillRect(pos.x - 14 + i * 3, pos.y - 12, 2, 3, col * 0.5);
				}
			}
			else {
				
				double ang = random::floatRandom(0, 2 * M_PI, 3);
				image("ball", pos.x, pos.y, r * 2.5, r * 2.5, ang, {0, 0, 0});
				image("ball", pos.x, pos.y, r * 2, r * 2, ang, col);
				image("ball", pos.x, pos.y, r * 1.5, r * 1.5, ang, { 255, 255, 255 });
				//fillCircle(pos.x, pos.y, r-1, {0, 0, 0});
			}

			
		}

		double y = 10;
		if (comm == "TBL") {
			std::string token;
			std::string name;
			Color color(255, 255, 255);
			std::string kills;
			std::string deaths;
			while (ss >> token && ss >> name && ss >> color.r && ss >> color.g && ss >> color.b && ss >> kills && ss >> deaths) {
				std::string str = name + " " + kills + "X" + deaths;
				text(str, 50, y, 20, color);
				std::cout << str << "\n";
				y += 20;
			}
		}
	}

}
