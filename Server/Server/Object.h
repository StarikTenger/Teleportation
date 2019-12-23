#pragma once
#include <string>
#include "geometry.h"
#include "Color.h"

class Object {
public:
	Vector2d pos;
	Vector2d vel;
	int type = 0;
	int hp = 10;
	int active = 1;

	std::string token = "petrovich";
	std::string name = "Biba";

	double cooldown = 0.5;
	double timeToCooldown = 0;
	double r = 8;
	double afkTime = 10;

	double countdown = 0;

	Color color;

	Object() {};
	~Object() {};
};

