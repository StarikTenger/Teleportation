#pragma once
#include <string>
#include "geometry.h"
#include "Color.h"

class Particle {
public:
	Vector2d pos;
	Vector2d vel;

	Color col;

	double r = 1;
	double rVel = 0;
	double timeLeft = 0;

	std::string image;

	Particle();
	Particle(std::string _image, Vector2d _pos, Vector2d _vel, double _r, double _rVel, Color _col, double _timeLeft);
};

