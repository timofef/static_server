#include <iostream>
#include <unistd.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <sys/socket.h>
#include "Client.h"
#include "Parser.cpp"

Client::Client(int sock, std::string doc): socket(sock), document_root(doc){}

Client::~Client() {
    if (socket) {
        close(socket);
    }
}

void Client::serve() {
    std::string requestStr = read();
    try {
        int isParsed = parse(request, requestStr);
        if (isParsed) {
            handler(request, response, document_root, );
            write();
        } else {
            error_handler(response, request);
            write("", 0);
        }
    }
    catch (std:: exception& ex) {
        std::cout << "exception:   " << ex.what() << std::endl;
    }
}

std::string Client::read() const {

}

void Client::write(const std::string &path, int size_file) {
    send(response.data(), response.size());

    if (request.method == "GET" && !path.empty()) {
        sendfile(path, size_file);
    }
}

void Client::sendfile(const std::string &path, int size_file) {
    int fd = open(path.c_str(), 0);
    ::sendfile(socket, fd, 0, size_file);
    close(fd);
}

void Client::send(const char *start, int size) const {
    size_t left = size;
    ssize_t sent = 0;
    int flags = 0;

    while (left > 0) {
        sent = ::send(socket, start + sent, size - sent, flags);
        if (-1 == sent)
            throw std::runtime_error("write failed: " + std::string(strerror(errno)));
        left -= sent;
    }
}


