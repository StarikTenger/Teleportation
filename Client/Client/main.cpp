#include "Control.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#include "network.h"

#pragma warning(disable: 4996)

int main() {
	Control control;

	control.loadConfig("config.conf");

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
		control.events();

		std::string command;
		command += control.name + " ";
		command += std::to_string(control.mouse.pos.x) + " ";
		command += std::to_string(control.mouse.pos.y) + " ";
		command += std::to_string(control.mouse.state) + " ";
		command += std::to_string((int)control.color.r) + " ";
		command += std::to_string((int)control.color.g) + " ";
		command += std::to_string((int)control.color.b) + " ";

		send(connection, command);
		std::string s = recv(connection);
		std::cout << s << std::endl;

		control.drawSys.draw(s);
		control.drawSys.window->display();
	}

	system("pause");
	return 0;
}