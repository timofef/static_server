#ifndef STATIC_SERVER_CLIENT_H
#define STATIC_SERVER_CLIENT_H


class Client {
public:
    Client(int sock, std::string doc);
    ~Client();
    void serve();
private:
    int socket;
    std::string document_root;
    Request request;
    std::string response;

    std::string read() const;
    void write(const std::string& path, int size_file);
    void sendfile(const std::string& path, int size_file);
    void send(const char* start, int size) const;
};


#endif //STATIC_SERVER_CLIENT_H
