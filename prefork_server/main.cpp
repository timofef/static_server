#include <iostream>
#include <unistd.h>

#include "Config.h"
#include "Server.h"


#define SERVER_PORT 8085

int main() {
    Config config;
    int isOk = config.readConfig("/httpd.conf");
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
            client.serve();
        }
    }
    catch (std:: exception& ex) {
        std::cout << "exception:   " << ex.what() << std::endl;
    }

    std::cout << "Prefork server successfully started at port " << SERVER_PORT << std::endl;

    return 0;
}
