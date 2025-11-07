#include "../LocalIPC.hpp"

int main() {
        LocalIPC::Client client(55555);

        client.Send(std::vector<uint8_t>({'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}));

        return 0;
}