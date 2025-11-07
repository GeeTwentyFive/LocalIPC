# Usage
1) `#include "LocalIPC.hpp"`
2) `LocalIPC::Server server(<PORT>)` or `LocalIPC::Client client(<PORT>)`
3) `.Send(data)` / `data = .Recv()`

# Example:
Server:
```
#include <iostream>
#include "LocalIPC.hpp"

int main() {
        LocalIPC::Server server(55555);

        std::vector<uint8_t> data = server.Recv();

        data.push_back('\0');
        std::cout << data.data() << std::endl;

        return 0;
}
```

Client:
```
#include "LocalIPC.hpp"

int main() {
        LocalIPC::Client client(55555);

        client.Send(std::vector<uint8_t>({'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}));

        return 0;
}
```