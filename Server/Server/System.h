#pragma once
#include <vector>
#include <fstream>
#include "Vector2d.h"
#include <deque>
#include <string>
#include <SFML/Graphics.hpp>

#include "Object.h"
#include "Points.h"

class System{
public:
	double dt = 0.02;
	double defaultVel = 150;

	std::vector<Object> objects;

	Vector2d border = { 800, 800 };

	std::deque<std::string> commands;

	std::map<std::string, Points> table;

	System();
	~System();

	void step();
	void shoot(std::string name, Vector2d pos);
};