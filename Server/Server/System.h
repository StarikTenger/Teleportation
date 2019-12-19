#pragma once
#include <vector>
#include <fstream>
#include "Vector2d.h"
#include <deque>
#include <string>
#include <SFML/Graphics.hpp>

#include "Object.h"

class System{
public:
	double dt = 0.02;
	std::vector<Object> objects;

	double defaultVel = 150;

	std::deque<std::string> commands;

	System();
	~System();

	void step();
	void shoot(std::string name, Vector2d pos);
};