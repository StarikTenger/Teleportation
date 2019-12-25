#include "Particle.h"

Particle::Particle(){}

Particle::Particle(std::string _image, Vector2d _pos, Vector2d _vel, double _r, double _rVel, Color _col, double _timeLeft) {
	image = _image;
	pos = _pos;
	vel = _vel;
	r = _r;
	rVel = _rVel;
	col = _col;
	timeLeft = _timeLeft;
}