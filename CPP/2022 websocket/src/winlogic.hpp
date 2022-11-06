#pragma once

#ifndef WINLOGIC_HPP
#define WINLOGIC_HPP

	#include <map>
	#include <vector>

	#include "winsocks.hpp"

	namespace winsocks {

		/*получает строку типа "HTTP/1.1 200 OK\r\n
		Content-Type: image/jpeg; charset=utf-8\r\n
		Content-Length: 19912\r\n\r\n" и преобразует в контейнер */
		std::vector<std::pair<std::string, std::string>> vector_former(std::stringstream& _ss);
		
		std::string responser(const std::string& _buff);

		bool myLogic(SOCKET*, SOCKET*);
	}

#endif // !WINLOGIC_HPP




