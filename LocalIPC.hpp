#include <cstdint>
#include <vector>
#include <iostream>
#include <string>

#if defined(__linux__) or defined(unix)
#include <sys/socket.h>
#include <unistd.h>

#elif defined(_WIN32)
#include <winsock2.h>

#endif


namespace LocalIPC {
        class Server : public _Common {
        public:
                Server(uint16_t port) : _Common(port) {
#if defined(__linux__) or defined(unix)
                        // TODO

#elif defined(_WIN32)
                        // TODO

#endif
                }
        };

        class Client : public _Common {
        public:
                Client(uint16_t port) : _Common(port) {
#if defined(__linux__) or defined(unix)
                        // TODO

#elif defined(_WIN32)
                        // TODO

#endif
                }
        };



        class _Common {

        protected:
#if defined(__linux__) or defined(unix)
                        int sock;

#elif defined(_WIN32)
                        SOCKET sock = INVALID_SOCKET;

#endif



        public:
                _Common(uint16_t port) {
#if defined(__linux__) or defined(unix)
                        sock = socket(AF_INET, SOCK_STREAM, 0);
                        if (sock == -1) throw std::runtime_error(
                                std::string("ERROR: Failed to create socket, with errno: ") + std::to_string(errno)
                        );

                        // TODO

#elif defined(_WIN32)
                        WSADATA wsaData;
                        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
                        if (result != 0) throw std::runtime_error(
                                std::string("ERROR: Failed to initialize Winsock, with WSAGetLastError() code: ") + std::to_string(WSAGetLastError())
                        );

                        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                        if (sock == INVALID_SOCKET) throw std::runtime_error(
                                std::string("ERROR: Failed to create socket, with WSAGetLastError() code: ") + std::to_string(WSAGetLastError())
                        );

#endif
                }



                ~_Common() {
#if defined(__linux__) or defined(unix)
                        close(sock);

#elif defined(_WIN32)
                        WSACleanup();

#endif
                }



                void Send(std::vector<uint8_t> data) {
                        int result = send(sock, (const char*)data.data(), data.size(), 0);
                        if (result == -1) throw std::runtime_error(
                                std::string("ERROR: Failed to send data")
#if defined(__linux__) or defined(unix)
                                + ", with errno: " + std::to_string(errno)

#elif defined(_WIN32)
                                + ", with WSAGetLastError() code: " + std::to_string(WSAGetLastError())

#endif
                        );
                }



                std::vector<uint8_t> Recv(size_t amount) {
                        std::vector<uint8_t> data;
                        data.resize(amount);

                        ssize_t amount_read = recv(sock, data.data(), amount, MSG_WAITALL);
                        if (amount_read != amount) return std::vector<uint8_t>();

                        return data;
                }



        };
}