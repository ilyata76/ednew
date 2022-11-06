#ifdef _WIN32
    #include "winsocks.hpp"
    #include "winlogic.hpp"
#endif

int main(int argc, char** argv) {

    #ifdef _WIN32

        winsocks::Server S("127.0.0.1", "8000");
        
        S.run(winsocks::myLogic); // [](SOCKET* listen_socket, SOCKET* client_socket)->bool {}

    #endif

    return 0;
}
