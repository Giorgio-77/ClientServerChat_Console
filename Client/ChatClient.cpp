#include <iostream>
#include <limits>
#include <csignal>
#include "../Lib/Client.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;
using namespace Socket;

Client* chat_client = nullptr;

void signalHandler(int);
void printMessage(const string&);

int main(int argc, char** argv) {

	signal(SIGINT, signalHandler);

	cout << "Configure Client..." << endl;
	// IP
	string server = "127.0.0.1";

	// Server listening port 
	int port = 5000;
	cout << "Port: ";
	cin >> port;

	try {
		chat_client = new Client(server, port);
		chat_client->setOnMessage(printMessage);
		chat_client->connectServer();
		delete chat_client;
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}

	system("pause");
	return 0;
}

void signalHandler(int code) {
	char ch;
	cout << "Are you sure you want to close socket?(Y/N)";
	cin >> ch;
	if (toupper(ch) == 'Y' && chat_client != nullptr) {
		delete chat_client;
		exit(0);
	}
	cin.clear();
	cin.ignore(32767, '\n');
}

void printMessage(const string& t_message) {
	std::cout << t_message << std::endl;
}