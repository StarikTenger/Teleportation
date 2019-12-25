#pragma once
#include <string>
#include "Color.h"

class Characteristic {
public:
	std::string name = "qqq";
	int kills = 0;;
	int deaths = 0;

	Color color;

	Characteristic() {};
	~Characteristic() {};
};

