#pragma once

#ifndef WINSOCKS_HPP
#define WINSOCKS_HPP
	
	#include <iostream>
	#include <sstream>
	#include <string>
	#include <algorithm>

	#include <WinSock2.h> // подключаем библиотеку
	#include <WS2tcpip.h> // для работы с TCP IP протоколами

	namespace winsocks {

		class Server {

			// https://docs.microsoft.com/ru-ru/windows/win32/winsock/complete-server-code

			private:
				WSAData* wsa_data; // для хранения служебной информации windows sockets
				struct addrinfo* addr; // структура хранит информацию об IP-адресе слушающего (текущего) сокета
				struct addrinfo* hints; // шаблон для иницилазиации структуры адреса
				SOCKET* listen_socket; // идентификатор сокета сервера
				SOCKET* client_socket; // идентификатор входящего сокета от клиента
				PCSTR IP; // IP адрес
				PCSTR port; // порт

			public:
				
				Server();

				Server(PCSTR _IP, PCSTR _port);
				
				void run(bool (*acceptLogic)(SOCKET*, SOCKET*), void* _v = NULL);
				void close();
				
				~Server();
		};

		
	}


#endif // !WINSOCKS_HPP