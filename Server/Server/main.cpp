#include "Control.h"
#include "network.h"

void gameLoop(Control& control) {
	while (1) {
		//g_mutex.lock();
		control.step();
		//g_mutex.unlock();
	}
}

void conn(SOCKET& connection, Control& control) {
	while (1) {
		//g_mutex.lock();
		std::string s = recv(connection);
		if (!s.size()) {
			g_mutex.unlock();
			break;
		}
		std::cout << "\n" << s << "\n";
		control.command(s);
		std::string msg = control.message();
		
		send(connection, msg);
		//g_mutex.unlock();
	}
}

int main(){
	random::start();
	
	Control control;
	std::thread game(gameLoop, std::ref(control));
	game.detach();


	startup();

	Address address("192.168.0.12", 1111);
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