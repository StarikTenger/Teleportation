#include "geometry.h"
#include "System.h"
#include "random.h"
#include "Color.h"
#include <iostream>
#include <sstream>
#include <math.h>

void System::step() {
	// commands
	while (commands.size()) {
		std::string s = commands.front();
		commands.pop_front();

		std::stringstream ss;
		ss << s;
		std::string name;
		Vector2d pos;
		Color col;
		int state;
		ss >> name;
		ss >> pos.x >> pos.y;
		ss >> state;	
		ss >> col.r >> col.g >> col.b;
		//std::cout << col.r << " " << col.g << " " <<  col.b << "\n";
		for (auto& p : objects) {
			if (p.team == name)
				p.color = col;
		}
		if (state)
			shoot(name, pos);

	}

	for (auto& p : objects) {
		p.pos += p.vel * dt;
		if (p.type == 1) {
			p.countdown -= dt;
		}
	}

	// collisions
	for (auto& bullet : objects) {
		if (bullet.type == 0)
			continue;
		for (auto& victim : objects) {
			if (victim.team == bullet.team)
				continue;
			if (geom::distance(victim.pos, bullet.pos) < victim.r + bullet.r) {
				victim.hp--;
				bullet.countdown = -1;
				bullet.active = 0;
			}
		}
	}

	// teleport & delete
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].type == 1 && objects[i].countdown <= 0) {
			if(objects[i].active)
				for (auto& p : objects) {
					if (p.type == 0 && p.team== objects[i].team) {
						p.pos = objects[i].pos;
						break;
					}
				}
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}