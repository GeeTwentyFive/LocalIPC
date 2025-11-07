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
                        this->sock = socket(AF_INET, SOCK_STREAM, 0);
                        if (this->sock == -1) throw std::runtime_error(
                                std::string("ERROR: Failed to create socket, with errno: ") + std::to_string(errno)
                        );

                        // TODO

#elif defined(_WIN32)
                        WSADATA wsaData;
                        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
                        if (result != 0) throw std::runtime_error(
                                std::string("ERROR: Failed to initialize Winsock, with WSAGetLastError() code: ") + std::to_string(WSAGetLastError())
                        );

                        this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                        if (this->sock == INVALID_SOCKET) throw std::runtime_error(
                                std::string("ERROR: Failed to create socket, with WSAGetLastError() code: ") + std::to_string(WSAGetLastError())
                        );

#endif
                }



                ~_Common() {
#if defined(__linux__) or defined(unix)
                        close(this->sock);

#elif defined(_WIN32)
                        closesocket(this->sock);

#endif
                }



                //
                // Returns number of bytes sent, or -1 on error
                //
                int Send(std::vector<uint8_t> data) {
                        data.insert(data.begin(), {
                                (uint8_t)((data.size() >> 0) & 0xFF),
                                (uint8_t)((data.size() >> 8) & 0xFF),
                                (uint8_t)((data.size() >> 16) & 0xFF),
                                (uint8_t)((data.size() >> 24) & 0xFF)
                        });
                        return send(this->sock, (const char*)data.data(), data.size(), 0);
                }



                //
                // Returns empty vector on error
                //
                std::vector<uint8_t> Recv() {
                        ssize_t amount_read = 0;

                        int data_size = 0;
                        amount_read = recv(this->sock, &data_size, sizeof(int), 0);
                        if (amount_read != sizeof(int)) return std::vector<uint8_t>();

                        std::vector<uint8_t> data;
                        data.resize(data_size);

                        amount_read = recv(this->sock, data.data(), data_size, MSG_WAITALL);
                        if (amount_read != data_size) return std::vector<uint8_t>();

                        return data;
                }



        };
}