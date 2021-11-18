#pragma once
#ifndef SERVER_H
#define SERVER_H

#include "NodeV4.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>

namespace Socket {

	class Server : protected NodeV4 {
	protected:
		void setDefault();

		// message event function
		std::function<void(const std::string& t_message) > m_onMessage = nullptr;
		void showMessage(const std::string& t_message);

		// thread
		std::vector<std::thread> v_thread;
		void joinThread();
		mutable std::mutex m_mu;

		// client
		int m_nodeSize = 0;
		std::vector<NodeV4*> v_client;
		void closeClient();

		// server
		int m_connectionSize = 128;
		void createServer();
		void bindServer();
		void listenServer();
		void handleRequest();

		// Message
		void sendMessageClients(const std::string& t_message);
		void sendMessageAll(const std::string& t_message, const int& t_socket);

	public:
		Server();
		Server(const int& t_port);
		Server(const int& t_port, const int& t_connectionSize);

		void setOnMessage(const std::function<void(const std::string&) >& t_function);

		void runServer();
		void closeServer();

		virtual ~Server();
	};
}

#endif /* SERVER_H */




