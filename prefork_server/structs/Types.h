#ifndef STATIC_SERVER_TYPES_H
#define STATIC_SERVER_TYPES_H

#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> mime_types = { {".txt", "text/plain"},
                                                            {".html", "text/html"},
                                                            {".css", "text/css"},
                                                            {".js", " text/javascript"},
                                                            {".png", "image/png"},
                                                            {".jpg", "image/jpeg"},
                                                            {".jpeg", "image/jpeg"},
                                                            {".png", "image/png"},
                                                            {".swf", "application/x-shockwave-flash"},
                                                            {".gif", "image/gif"},
                                                            {".mp4", "video/mp4"}};

std::string get_mime_type(std::string extension) {
    std::transform(extension.begin(), extension.end(), extension.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    auto it = mime_types.find(extension);
    if (it == mime_types.end()) {
        return "application/octet-stream";
    }

    return it->second;
}

#endif //STATIC_SERVER_TYPES_H
