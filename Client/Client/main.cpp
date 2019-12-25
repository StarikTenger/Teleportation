#include "Control.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#include "network.h"
#include "getMilliCount.h"

#pragma warning(disable: 4996)

std::string makeToken() {
	std::string token;

	{
		std::ifstream tokenFile("token.conf");
		tokenFile >> token;
		tokenFile.close();
	}

	if (token == "") {
		std::string symbols = "0123456789";
		for (int i = 0; i < 8; i++) {
			token += symbols[random::intRandom(0, symbols.size() - 1)];
			std::ofstream tokenFile("token.conf");
			tokenFile << token;
			tokenFile.close();
		}
	}
	
	return token;
}

int main() {
	random::start();

	Control control;

	control.loadConfig("config.conf");
	std::string token = makeToken();

	//WSAStartup
	startup();

	Address address(control.address.c_str(), control.port);
	int sizeofaddr = sizeof(address.addr);

	SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connection, (SOCKADDR*)&address.addr, sizeof(address.addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";

	

	while (1) {
		int64_t timePrev = 0;
		timePrev = getMilliCount();
		control.events();

		std::string command;
		command += token + " ";
		command += control.name + " ";
		command += std::to_string(control.mouse.pos.x) + " ";
		command += std::to_string(control.mouse.pos.y) + " ";
		command += std::to_string(control.mouse.state) + " ";
		command += std::to_string((int)control.color.r) + " ";
		command += std::to_string((int)control.color.g) + " ";
		command += std::to_string((int)control.color.b) + " ";

		send(connection, command);
		std::string s = recv(connection);

		if (s == "") {
			closesocket(connection);
			connection = socket(AF_INET, SOCK_STREAM, NULL);
			if (connect(connection, (SOCKADDR*)&address.addr, sizeof(address.addr)) != 0) {
				std::cout << "Error: failed connect to server.\n";
				return 1;
			}
		}

		std::cout << getMilliCount() - timePrev << "\n";

		control.drawSys.step((getMilliCount() - timePrev) / 1000.0);
		control.drawSys.draw(s);
		control.drawSys.window->display();
	}

	system("pause");
	return 0;
}