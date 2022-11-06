#include "winsocks.hpp"

winsocks::Server::Server() {
	this->IP = NULL;
	this->port = NULL;

	this->wsa_data = new WSAData{ NULL };
	this->addr = new addrinfo{ NULL };
	this->hints = new addrinfo{ NULL };
	this->listen_socket = new SOCKET{ INVALID_SOCKET };
	this->client_socket = new SOCKET{ INVALID_SOCKET };
}

winsocks::Server::Server(PCSTR _IP, PCSTR _port) {
	this->IP = _IP;
	this->port = _port;

	this->wsa_data = new WSAData{ NULL };
	this->addr = new addrinfo{ NULL };
	this->hints = new addrinfo{ NULL };
	this->listen_socket = new SOCKET{ INVALID_SOCKET };
	this->client_socket = new SOCKET{ INVALID_SOCKET };
}

void winsocks::Server::run(bool (*acceptLogic)(SOCKET*, SOCKET*), void* _v) {
	WORD dll_version = MAKEWORD(2, 1); // запрашиваемая версия DLL библиотеки

	auto result = WSAStartup(dll_version, this->wsa_data);
	if (result != 0) {
		std::cerr << "Библиотека не загрузилась: " << result << "\n";
		return;
		//throw std::exception("dll has been not loaded");
	}; // загрузка библиотеки WSA, инициализация WinSock

	this->hints->ai_family = AF_INET; // интернет
	this->hints->ai_socktype = SOCK_STREAM; // потоковый тип сокета
	this->hints->ai_protocol = IPPROTO_TCP; // TCP IP протокол
	this->hints->ai_flags = AI_PASSIVE; // биндинг на адрес для принятия входящих соединений

	// инициализируем addr
	result = getaddrinfo(this->IP, this->port, this->hints, &this->addr);
	if (result != 0) {
		std::cerr << "getaddrinfo failed : " << result << "\n";
		WSACleanup();
		return;
		//throw std::exception("getaddrinfo failed");
	};

	// создаём сокет
	*this->listen_socket = socket(this->addr->ai_family, this->addr->ai_socktype, this->addr->ai_protocol);

	if (*this->listen_socket == INVALID_SOCKET) {
		std::cerr << "socket failed : " << result << "\n";
		freeaddrinfo(this->addr);
		WSACleanup();
		return;
	}

	// связываем его с IP-адресом
	result = bind(*this->listen_socket, this->addr->ai_addr, this->addr->ai_addrlen);

	if (result == SOCKET_ERROR) {
		std::cerr << "bind failed : " << result << "\n";
		closesocket(*this->listen_socket);
		freeaddrinfo(this->addr);
		WSACleanup();
		return;
	}

	// инициализация сокета
	result = listen(*this->listen_socket, SOMAXCONN);

	if (result == SOCKET_ERROR) {
		std::cerr << "listen failed : " << result << "\n";
		closesocket(*this->listen_socket);
		freeaddrinfo(this->addr);
		WSACleanup();
		return;
	}

	// функция с логикой принятия входящих соединений
	bool res = acceptLogic(this->listen_socket, this->client_socket);

	if (!res) {
		std::cerr << "acceptLogic failed" << "\n";
	}

	closesocket(*this->listen_socket);
	closesocket(*this->client_socket);
	freeaddrinfo(this->addr);
	WSACleanup();

	return;
}

void winsocks::Server::close() {
}

winsocks::Server::~Server() {
	//std::cout << "\n DESTRUCTOR ~SERVER() \n";
	delete this->wsa_data;
	// delete this->addr; // почему крашит?
	delete this->hints;
	delete this->listen_socket;
	delete this->client_socket;
}
