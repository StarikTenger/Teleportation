#include "geometry.h"
#include "System.h"
#include "random.h"
#include <iostream>
#include <math.h>

void System::shoot(std::string name, Vector2d pos) {
	for (auto& p : objects) {
		if (p.type == 1 && p.team == name) {
			return;
		}
	}

	for (auto& p : objects) {
		if (p.type == 0 && p.team == name) {
			Vector2d dir = geom::direction(pos, p.pos);
			Object obj;
			obj.team = p.team;
			obj.type = 1;
			obj.pos = p.pos;
			obj.vel = dir * defaultVel;
			obj.countdown = geom::distance(pos, p.pos) / defaultVel;
			objects.push_back(obj);
			break;
		}
	}
}