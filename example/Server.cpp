#include <iostream>
#include "../LocalIPC.hpp"

int main() {
        LocalIPC::Server server(55555);

        std::vector<uint8_t> data = server.Recv();

        data.push_back('\0');
        std::cout << data.data() << std::endl;

        return 0;
}