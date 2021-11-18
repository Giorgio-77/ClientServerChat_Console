#include <iostream>
#include <limits>
#include <csignal>
#include "../Lib/Server.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;
using namespace Socket;

Server* chat_server = nullptr;

void signalHandler(int);
void printMessage(const string&);

int main(int argc, char** argv) {

	signal(SIGINT, signalHandler);

	cout << "Configure Server..." << endl;
	// port
	int port = 5000;
	cout << "Port: ";
	cin >> port;

	// Number of connections
	int connection_size = 16;
	cout << "Connections: ";
	cin >> connection_size;

	try {
		chat_server = new Server(port, connection_size);
		chat_server->setOnMessage(printMessage);
		chat_server->runServer();
		delete chat_server;
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}

	return 0;
}

void signalHandler(int code) {
	char ch;
	cout << "Are you sure you want to close socket?(Y/N)";
	cin >> ch;
	if (toupper(ch) == 'Y' && chat_server != nullptr) {
		delete chat_server;
		exit(0);
	}
	cin.clear();
	cin.ignore(32767, '\n');
}

void printMessage(const string& t_message) {
	std::cout << "> " << t_message << std::endl;
}