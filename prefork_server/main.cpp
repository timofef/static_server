#include <iostream>
#include <unistd.h>

#include "Config.h"
#include "Server.h"
#include "Client.h"


#define SERVER_PORT 80

int main() {
    Config config;
    int isOk = config.readConfig("/etc/httpd.conf");
    if (!isOk) {
        std::cout << "Can't parse config" << std::endl;
        return -1;
    }

    try {
        Server server(SERVER_PORT, &config);
        for (int i = 0; i < config.cpu_limit; ++i) {
            pid_t pid;

            //pid = fork();

            if ((pid = fork())) {
                break;
            } else if (pid < 0) {
                std::cout << "Failed to fork" << std::endl;
            }
        }

        while (1) {
            std::shared_ptr<Client> client = server.connect();
            client->serve();
        }
    }
    catch (std:: exception& ex) {
        std::cout << "exception:   " << ex.what() << std::endl;
    }

    return 0;
}
