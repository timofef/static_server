#include <iostream>
#include <unistd.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <cstring>
#include "Client.h"
#include "Parser.h"
#include "Handler.h"

Client::Client(int sock, std::string doc): socket(sock), document_root(doc){}

Client::~Client() {
    if (socket) {
        close(socket);
    }
}

void Client::serve() {
    std::string requestStr = read();
    try {
        int isParsed = parse(requestStr, request);
        if (isParsed) {
            std::string path;
            int file_size = handler(request, response, document_root, path);
            write(path, file_size);
        } else {
            errorHandler(response);
            write("", 0);
        }
    }
    catch (std:: exception& ex) {
        std::cout << "exception:   " << ex.what() << std::endl;
    }
}

std::string Client::read() const {
    std::string result;
    int bytes = 8000;
    char *buf = new char[bytes];
    size_t r = 0;
    while (r != bytes) {
        ssize_t rc = ::recv(socket, buf + r, bytes - r, 0);
        if (rc == -1 || rc == 0) {
            delete [] buf;
            throw std::runtime_error("read failed: " + std::string(strerror(errno)));
        }

        r += rc;
        result.append(buf, rc);
        if (result.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }

    delete [] buf;
    return result;
}

void Client::write(const std::string &path, int size_file) {
    send(response.data(), response.size());

    if (request.method == "GET" && !path.empty()) {
        int fd = open(path.c_str(), 0);
        ::sendfile(socket, fd, 0, size_file);
        close(fd);
    }
}

void Client::send(const char *str, int size) const {
    size_t left = size;
    ssize_t sent = 0;
    int flags = 0;

    while (left > 0) {
        sent = ::send(socket, str + sent, size - sent, flags);
        if (!sent)
            throw std::runtime_error("write failed: " + std::string(strerror(errno)));
        left -= sent;
    }
}


