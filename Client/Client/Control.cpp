#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>

Control::Control() {
	for (int i = 0; i < 100; i++) {
		keyMatches.push_back({});
	}
	std::ifstream keys("keys.conf");
	while (keys) {
		std::string key;
		keys >> key;
		while (keys) {
			std::string key1;
			keys >> key1;
			if (key1 == "END")
				break;
			keyMatches[getKey(key1)].push_back(getKey(key));

		}
	}
}

Control::~Control() {

}

Vector2d Control::getCursorPos() {
	return geom::rotate((mouse.pos - drawSys.cam.border/2) / drawSys.cam.scale, drawSys.cam.angle);
}

void Control::loadConfig(std::string path) {
	std::ifstream file(path);
	std::string comm;
	while (file >> comm) {
		if (comm == "NAME")
			file >> name;
		if (comm == "ADDRESS")
			file >> address;
		if (comm == "PORT")
			file >> port;
		if (comm == "COLOR")
			file >> color.r >> color.g >> color.b;
	}
	file.close();
}


void Control::saveConfig() {
	
}

void Control::step() {
	int timeMs = getMilliCount();
	if (timeMs - timePrev > dt) {
		timePrev = timeMs;

		
		events();
		drawSys.mouse = mouse;
		
		
		for (int i = 0; i < 1; i++) {
			sys.step();
		}
		

		drawSys.system = &sys;
		//drawSys.draw();
		//drawSys.window->display();

		
	}
}
