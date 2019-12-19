#pragma once
#include <vector>
#include <fstream>
#include "Vector2d.h"
#include <string>
#include <SFML/Graphics.hpp>


class System{
public:
	double dt = 0.02;

	System();
	~System();

	void step();
};