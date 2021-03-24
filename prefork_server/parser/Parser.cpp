#include <string>
#include <sstream>
#include "Request.h"

int parse(const std::string from, Request *to) {
    std::stringstream ss(from);
    ss >> to.method;
    ss >> to.uri;

    std::string input;
    while (ss >> input) {
        if (to.method == "GET" ||
            to.method == "HEAD" ||
            to.method == "OPTIONS" ||
            to.method == "PUT" ||
            to.method == "DELETE" ||
            to.method == "POST") {
            return 1;
        } else {
            return -1;
        }
    }
}
