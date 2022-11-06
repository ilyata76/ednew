#include "winlogic.hpp"

std::vector<std::pair<std::string, std::string>> winsocks::vector_former(std::stringstream& _ss) {
    std::vector<std::pair<std::string, std::string>> result;
    std::string line;
    
    for (int i = 0; std::getline(_ss, line).good(); ++i) {

        if (i == 0) {
            size_t index1 = line.find('T', 0);

            if (index1 != std::string::npos) result.push_back({ line.substr(0, index1 + 1) , line.substr(index1 + 2, line.size()) });
        } else { 
            size_t index = line.find(':', 0);

            if (index != std::string::npos) result.push_back({ line.substr(0, index) , line.substr(index + 2, line.size()) });

        };

        line.clear();
    }

    return result;
}

std::string winsocks::responser(const std::string& _buff) {
    std::stringstream response; // полный ответ (с заголовками)
    std::stringstream response_body; // тело ответа

    auto map = vector_former(std::stringstream{ _buff });

    response_body << "raw: \n\n" << _buff << "\n\n\n";

    response_body << "processed: \n\n";
    for (const auto& kv : map) {
        response_body << kv.first << "\t-\t" << kv.second << '\n';
    } response_body << "\n\n\n";

    response_body << "endpoint: " << [](std::string _str)->std::string { 
        size_t index = _str.find('H');
        return (index != std::string::npos ? _str.substr(0, index - 1) : "error");
    }(map[0].second);

    // полноценный ответ
    response << "HTTP/1.1 200 OK\r\n"
        << "Version: HTTP/1.1\r\n"
        << "Content-Type: text; charset=utf-8\r\n" // content-type
        << "Content-Length: " << response_body.str().length()
        << "\r\n\r\n"
        << response_body.str();

    return response.str();
}

bool winsocks::myLogic(SOCKET* listen_socket, SOCKET* client_socket) {
    do {
        // принимаем входящий сокет
        *client_socket = accept(*listen_socket, NULL, NULL);
        if (*client_socket == INVALID_SOCKET) {
            std::cerr << "accept failed: " << WSAGetLastError() << "\n";
            return false;
        }

        //closesocket(*listen_socket); // уже не нужен (если без цикла)

        const int max_client_buffer_size = 1024;
        char buff[max_client_buffer_size];

        // получаем данные
        auto result = recv(*client_socket, buff, max_client_buffer_size, 0);

        if (result == SOCKET_ERROR) {
            std::cerr << "recv failed: " << result << "\n";
            return false;
        }
        else if (result == 0) {
            std::cerr << "connection closed" << "\n";
        }
        else {
            buff[result] = '\0'; // фактический размер данных - result;
        }

        // ФОРМИРУЕМ ОТВЕТ
        auto response_str = responser(std::string{ buff });

        // Отправляем ответ клиенту
        result = send(*client_socket, response_str.c_str(),
            response_str.length(), 0);

        if (result == SOCKET_ERROR) {
            std::cerr << "send failed: " << WSAGetLastError() << "\n";
        }

        // Закрываем соединение к клиентом
        closesocket(*client_socket);

    } while (true);


    return true;
}