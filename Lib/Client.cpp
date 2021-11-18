#include "Client.h"

namespace Socket {

	void Client::setDefault() {
		inet_pton(AF_INET, this->m_serverName.c_str(), &this->m_socketInfo.sin_addr);
	}

	void Client::showMessage(const std::string& t_message) {
		if (this->m_onMessage != nullptr) {
			this->m_onMessage(t_message);
		}
	}

	void Client::_connectServer() {
		this->createSocket();

		if (connect(this->m_socketFd, reinterpret_cast<sockaddr*> (&this->m_socketInfo), this->m_addressLen) == -1) {
			throw std::runtime_error("could not connect to server");
		}
	}

	void Client::receiveMessage() {
		this->m_thread = std::move(std::thread([=] {
			int len;
			char* message_buffer = new char[this->getMessageSize()];

			while ((len = recv(this->m_socketFd, message_buffer, this->getMessageSize(), 0)) > 0) {
				message_buffer[len] = '\0';

				// parsing & decrypt
				std::string message = message_buffer;
				size_t pos = message.find_first_of(' ');
				std::string s[]{ message.substr(0, pos + 1), message.substr(pos + 1) };
				s[1] = XOR_Crypt::decrypt(s[1]);
				message = s[0] + s[1];

				showMessage(message);
				std::memset(message_buffer, '\0', sizeof(message_buffer));
			}
			this->m_state = STATE::CLOSED;
			delete[]message_buffer;
			}));
	}

	void Client::writeMessage() {
		std::string message = "";
		while (this->m_state == STATE::OPEN) {
			std::getline(std::cin, message);
			message = XOR_Crypt::encrypt(message);			// encrypt
			this->sendMessage(this->m_socketFd, message);
		}
	}

	Client::Client() :
		NodeV4() {
		setDefault();
	}

	Client::Client(const int& t_port) :
		NodeV4(t_port) {
		setDefault();
	}

	Client::Client(const std::string& t_serverName, const int& t_port) :
		NodeV4(t_port), m_serverName(t_serverName) {
		setDefault();
	}

	void Client::setOnMessage(const std::function<void(const std::string&)>& t_function) {
		m_onMessage = t_function;
	}

	void Client::connectServer() {
		this->_connectServer();
		showMessage("Connection successfully....");
		this->receiveMessage();
		this->writeMessage();
	}

	void Client::closeConnection() {
		this->closeSocket();
		if (this->m_thread.joinable()) {
			this->m_thread.join();
		}
	}

	Client::~Client() {
		this->closeConnection();
	}

}
