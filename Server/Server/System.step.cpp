#include "geometry.h"
#include "System.h"
#include "random.h"
#include "Color.h"
#include <iostream>
#include <sstream>
#include <math.h>

void System::step() {
	if (objects.size() == 1) {
		//*this = System();
	}

	// commands
	while (commands.size()) {
		std::string s = commands.front();
		commands.pop_front();

		std::stringstream ss;
		ss << s;
		std::string token;
		std::string name;
		Vector2d pos;
		Color col;
		int state;
		ss >> token;
		ss >> name;
		ss >> pos.x >> pos.y;
		ss >> state;	
		ss >> col.r >> col.g >> col.b;
		
		// table operations
		if (table.find(token) == table.end()) {
			table[token] = Points();
		}
		table[token].name = name;

		int objectFound = 0;
		for (auto& p : objects) {
			if (p.token == token) {		
				objectFound = 1;
				if (p.type == 0)
					p.afkTime = 5;
			}
		}

		if (!objectFound) {
			Object obj;
			obj.pos = Vector2d(random::intRandom(0, border.x), random::intRandom(0, border.y));
			obj.color = fromHSV(random::intRandom(0, 360), 1, 1);
			obj.token = token;
			objects.push_back(obj);
			table[token].color = obj.color;
		} 
		else if (state)
			shoot(token, pos);
		
	}

	// afk time
	for (auto& p : objects)
		if (p.type == 0)
			p.afkTime -= dt;


	// checking borders
	for (auto& p : objects) {
		p.pos += p.vel * dt;
		if (p.type == 1) {
			if (p.pos.x > border.x || p.pos.y > border.y || p.pos.x < 0 || p.pos.y < 0) {
				p.pos -= p.vel * dt;
				p.countdown = 0;
			}
			p.countdown -= dt;
		}
		else {
			p.timeToCooldown -= dt;
		}
	}

	// collisions
	for (auto& bullet : objects) {
		if (bullet.type == 0)
			continue;
		for (auto& victim : objects) {
			if (victim.token == bullet.token)
				continue;
			if (geom::distance(victim.pos, bullet.pos) < victim.r + bullet.r) {
				victim.hp--;
				bullet.countdown = -1;
				bullet.active = 0;
				if (victim.hp <= 0) {
					table[victim.token].deaths++;
					table[bullet.token].kills++;
				}
			}
		}
	}

	// teleport & delete
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].type == 1 && objects[i].countdown <= 0) {
			if(objects[i].active)
				for (auto& p : objects) {
					if (p.type == 0 && p.token== objects[i].token) {
						p.pos = objects[i].pos;
						break;
					}
				}
			objects.erase(objects.begin() + i);
			i--;
		}
		if (objects[i].hp <= 0 || objects[i].afkTime <= 0) {
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}