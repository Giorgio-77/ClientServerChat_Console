#include "NodeV4.h"

namespace Socket {

	void NodeV4::setSocketInfo() {
		this->m_addressLen = sizeof(this->m_socketInfo);
		std::memset(&this->m_socketInfo, 0, this->m_addressLen);
		this->m_socketInfo.sin_family = AF_INET;
		this->m_socketInfo.sin_port = htons(this->m_port);
	}

	NodeV4::NodeV4() {
		setSocketInfo();
	}

	NodeV4::NodeV4(const int& t_port) :
		m_port(t_port) {
		setSocketInfo();
	}

	int NodeV4::getPort() const {
		return m_port;
	}

	void NodeV4::setPort(const int& t_port) {
		m_port = t_port;
		setSocketInfo();
	}

	int NodeV4::getSocketFd() const {
		return m_socketFd;
	}

	void NodeV4::setSocketFd(const int& t_socketFd) {
		m_socketFd = t_socketFd;
	}

	sockaddr_in NodeV4::getSocketInfo() const {
		return m_socketInfo;
	}

	void NodeV4::setSocketInfo(const sockaddr_in& t_socketInfo) {
		m_socketInfo = t_socketInfo;
	}

	int NodeV4::getMessageSize() const {
		return m_messageSize;
	}

	STATE NodeV4::getState() const {
		return m_state;
	}

	void NodeV4::setState(const STATE& t_state) {
		m_state = t_state;
	}

	void NodeV4::setMessageSize(const int& t_messageSize) {
		m_messageSize = t_messageSize;
	}

	void NodeV4::createSocket() {

#ifdef _WIN32
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
			throw std::runtime_error("WSAStartup() failed");
		}
#endif

		this->m_socketFd = socket(AF_INET, SOCK_STREAM, 0);
		if (this->m_socketFd == -1) {
			throw std::runtime_error("could not create socket");
		}
		this->m_state = STATE::OPEN;
	}

	void NodeV4::sendMessage(const int& t_socketFd, const std::string& t_message) {
		send(t_socketFd, t_message.c_str(), t_message.size(), 0);
	}

	void NodeV4::closeSocket() {
		if (this->m_state == STATE::CLOSED) {
			return;
		}
#ifdef _WIN32
		if (::closesocket(this->m_socketFd) < 0) {
			throw std::runtime_error("Could not close socket");
		}
		::WSACleanup();
#else
		if (close(this->m_socketFd) < 0) {
			throw std::runtime_error("Could not close socket");
		}
#endif
		this->m_state = STATE::CLOSED;
	}

	NodeV4::~NodeV4() {
		closeSocket();
	}
}

