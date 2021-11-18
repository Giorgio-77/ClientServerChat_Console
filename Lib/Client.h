#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include "NodeV4.h"
#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <string>
#include "XOR_Crypt.h"

namespace Socket {

	class Client : protected NodeV4 {
	protected:
		void setDefault();

		// message event function
		std::function<void(const std::string& t_message) > m_onMessage = nullptr;
		void showMessage(const std::string& t_message);

		// server
		std::string m_serverName = "localhost";

		// thread
		std::thread m_thread;
		std::mutex m_mu;

		void _connectServer();
		void receiveMessage();
		void writeMessage();

	public:
		Client();
		Client(const int& t_port);
		Client(const std::string& t_serverName, const int& t_port);

		void setOnMessage(const std::function<void(const std::string&) >& t_function);

		void connectServer();
		void closeConnection();

		virtual ~Client();
	};

}

#endif /* CLIENT_H */

