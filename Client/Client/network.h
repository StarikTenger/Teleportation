#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#pragma once

#pragma warning(disable: 4996)

#define BUFFLEN 1024

std::mutex g_mutex;

struct Address {
	SOCKADDR_IN addr;
	int size;
	Address() {};
	Address(const char* host, int port) {
		size = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr(host);
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;
	};

};

std::string recv(SOCKET& sock) {
	char msg[BUFFLEN];
	int r = recv(sock, msg, sizeof(msg), NULL);
	if (r <= 0)
		return "";
	std::string s = std::string(msg);
	return s;
}

void send(SOCKET& sock, std::string s) {
	char msg[BUFFLEN];
	strcpy(msg, s.c_str());
	send(sock, msg, sizeof(msg), NULL);
}

void startup() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}
}


