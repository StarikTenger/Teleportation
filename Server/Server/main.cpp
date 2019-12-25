#include "Control.h"
#include "network.h"

void gameLoop(Control& control) {
	random::start();
	while (1) {
		control.step();
	}
}

void conn(SOCKET& connection, Control& control) {
	while (1) {
		
		std::string s = recv(connection);
		//std::cout << "\n" << s << "\n";

		if (s == "") {
			closesocket(connection);
			return;
		}

		g_mutex.lock();
		control.command(s);
		g_mutex.unlock();

		std::string msg = control.message();
		
		send(connection, msg);
		
	}
}

int main(){
	random::start();
	
	Control control;
	std::thread game(gameLoop, std::ref(control));
	game.detach();


	startup();

	// address from file
	std::ifstream configFile("config.conf");
	std::string host;
	int port;
	configFile >> host;
	configFile >> port;

	Address address(host, 1111);
	int sizeofaddr = sizeof(address.addr);

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&address.addr, sizeof(address.addr));
	listen(sListen, SOMAXCONN);

	std::vector<SOCKET> connections;

	while (1) {
		SOCKET newConnection;
		newConnection = accept(sListen, (SOCKADDR*)&address.addr, &sizeofaddr);
		std::cout << "Accepted\n";

		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			connections.push_back(newConnection);
			std::thread thr(conn, std::ref(connections.back()), std::ref(control));
			thr.detach();
		}
	}

	return 0;
}