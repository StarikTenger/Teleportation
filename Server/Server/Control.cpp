#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
	return { 0, 0 };//geom::rotate((mouse.pos - drawSys.cam.border/2) / drawSys.cam.scale, drawSys.cam.angle);
}

void Control::loadConfig() {
	
}


void Control::saveConfig() {
	
}

void Control::command(std::string s) {
	sys.commands.push_back(s);
}

std::string Control::message() {
	std::string msg = "";
	for (auto p : sys.objects) {
		msg += "OBJ ";
		msg += p.token + " ";
		msg += std::to_string(p.type) + " ";
		msg += std::to_string((int)p.pos.x) + " ";
		msg += std::to_string((int)p.pos.y) + " ";
		msg += std::to_string((int)p.r) + " ";
		msg += std::to_string((int)p.color.r) + " "  + std::to_string((int)p.color.g) + " " + std::to_string((int)p.color.b) + " ";
		msg += std::to_string(p.hp) + " ";
	}
	msg += "TBL ";
	for (const auto& p : sys.table) {
		msg += p.first + " ";
		msg += p.second.name + " ";
		msg += std::to_string(p.second.color.r) + " " + 
			std::to_string(p.second.color.g) + " " + 
			std::to_string(p.second.color.b) + " ";
		msg += std::to_string(p.second.kills) + " ";
		msg += std::to_string(p.second.deaths) + " ";
	}
	std::cout << msg.size() << "\n";
	return msg;
}

void Control::step() {
	int timeMs = getMilliCount();
	if (timeMs - timePrev > dt) {
		timePrev = timeMs;

		
		events();
		//drawSys.mouse = mouse;

		for (int i = 0; i < 1; i++) {
			sys.step();
		}
			
	}
}
