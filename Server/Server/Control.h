#pragma once
#include <ctime>
#include <algorithm>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "keys.h"
#include "DrawSystem.h"
#include "random.h"
#include "System.h"
#include "geometry.h"
#include "Mouse.h"
#include "Gamepad.h"

enum controlMode {
	MENU, GAME
};

class Control{
public:
	controlMode mode = MENU;

	System sys;
	//DrawSystem drawSys;
	Mouse mouse;
	Gamepad joystick;

	std::vector<bool> keys = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	std::vector<std::vector<int> > keyMatches;


	//time
	int dt = 20;
	int timePrev = 0;
	bool stop = 0;
	int iteration = 0;


	Control();
	~Control();

	void events();	
	void step();
	void command(std::string s);
	std::string message();
	Vector2d getCursorPos();
	std::string configParametersAdress = "parameters.conf";
	void loadConfig();
	void saveConfig();
};

