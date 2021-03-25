#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "Request.h"
#include "Types.h"

std::string url_decode(std::string& file_name) {
    std::string tmp;
    int j = 0;
    char ch;
    for (int i = 0; i < file_name.size(); ++i) {
        if (int(file_name[i]) == 37) {
            sscanf(file_name.substr(i + 1, 2).c_str(), "%x", &j);
            ch = static_cast<char>(j);
            tmp += ch;
            i += 2;
        } else {
            tmp += file_name[i];
        }
    }

    return tmp;
}

int handler(Request request, std::string& response, std::string document_root, std::string& path) {
    if (request.method != "GET" && request.method != "HEAD") {
        response = "HTTP/1.1 405 Method Not Allowed\r\nServer: PreforkServer\r\nConnection: close\r\n\r\n";
        return 0;
    }

    if (request.uri.find("../") != std::string::npos) {
        response = "HTTP/1.1 403 Forbidden\r\nServer: PreforkServer\r\nConnection: close\r\n\r\n";
        return 0;
    }

    auto pos = request.uri.find('?');
    if (pos != std::string::npos) {
        request.uri = request.uri.substr(0, pos);
    }

    request.uri = url_decode(request.uri);

    int slash;
    if ((slash = request.uri.rfind('/')) == request.uri.size() - 1) {
        if (slash > request.uri.rfind('.')) {
            response = "HTTP/1.0 404 Not Found\r\nServer: PreforkServer\r\nConnection: close\r\n\r\n";
            return 0;
        }
        request.uri += "index.html";
    }

    pos = request.uri.rfind('.');
    if (pos == std::string::npos) {
        response = "HTTP/1.0 400 Bad Request\r\nServer: PreforkServer\r\nConnection: close\r\n\r\n";
        return 0;
    }

    bool bad_path = false;
    path = document_root + request.uri;
    int size = 0;
    try {
        size = std::filesystem::file_size(path);
    }
    catch (std::filesystem::filesystem_error& e) {
        bad_path = true;
        std::cout << e.what() << '\n';
        if (request.uri.rfind("index.html") != std::string::npos) {
            response = "HTTP/1.0 403 Forbidden\r\nServer: PreforkServer\r\nConnection: close\r\n\r\n";
        } else {
            response = "HTTP/1.0 404 Not Found\r\nServer: PreforkServer\r\nConnection: close\r\n\r\n";
        }
    }
    if (bad_path) {
        return 0;
    }

    std::string mime_type = get_mime_type(request.uri.substr(pos));
    std::stringstream resp;
    resp << "HTTP/1.1 200 OK\r\n" << "Content-Type: " << mime_type << "\r\n"
         << "Server: PreforkServer\r\n" << "Content-Length: " << size
         << "\r\nConnection: close"
         << "\r\n\r\n";

    response = std::move(resp.str());

    return size;
}

void errorHandler(std::string& resp) {
    resp = "HTTP/1.0 400 Bad Request\r\nServer: PreforkServer\r\nConnection: close\r\n\r\n";
}

