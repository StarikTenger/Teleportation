#pragma once
#include <string>
#include "geometry.h"
#include "Color.h"

class Object {
public:
	Vector2d pos;
	Vector2d vel;
	int type = 0;
	std::string team = "petrovich";

	

	double r = 5;
	int hp = 10;
	int points = 0;

	// for bullet (type = 1)
	double countdown = 0;
	int active = 1;

	Color color;

	Object() {};
	~Object() {};
};

