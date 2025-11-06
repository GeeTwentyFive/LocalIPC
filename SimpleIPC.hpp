// TODO: Refactor such that it is split into two blocks: Linux/Unix and Windows

#include <cstdint>
#include <vector>
#include <iostream>
#include <string>

#if defined(__linux__) or defined(unix)
// TODO
#elif defined(_WIN32)
#include <winsock2.h>
#endif


namespace SimpleIPC {
        class Server : public _Common {
        public:
                Server(uint16_t port) {
                        // TODO
                }
        };

        class Client : public _Common {
        public:
                Client(uint16_t port) {
                        // TODO
                }
        };

        class _Common {
        protected:
                SOCKET sock = INVALID_SOCKET;

        public:
#if defined(__linux__)
                _Common() {
                        // TODO
                }
#elif defined(_WIN32)
                _Common() {
                        int result;

                        WSADATA wsaData;
                        result = WSAStartup(MAKEWORD(2, 2), &wsaData);
                        if (result != 0) throw std::runtime_error(
                                std::string("ERROR: Failed to initialize Winsock, with WSAGetLastError() code: ") + std::to_string(WSAGetLastError())
                        );

                        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                        if (sock == INVALID_SOCKET) throw std::runtime_error(
                                std::string("ERROR: Failed to initialize Winsock, with WSAGetLastError() code: ") + std::to_string(WSAGetLastError())
                        );
                }

                ~_Common() { WSACleanup(); }
#endif

#if defined(__linux__)
                void Send(std::vector<uint8_t> data) {
                        // TODO
                }
#elif defined(_WIN32)
                void Send(std::vector<uint8_t> data) {
                        int result = send(sock, (const char*)data.data(), data.size(), 0);
                        if (result == SOCKET_ERROR) throw std::runtime_error(
                                std::string("ERROR: Failed to send data, with WSAGetLastError() code: ") + std::to_string(WSAGetLastError())
                        );
                }
#endif

                std::vector<uint8_t> Recv() {
                        // TODO
                }
        };
}