#include "headers.h"

// Headers set method
void Headers::set(std::string key, std::string value) {
    headers[key] = value;
}

// Headers get method
std::string Headers::get(std::string key) {
    return headers[key];
}

// Headers to_string method
std::string Headers::to_string() {
    std::string result = "";

    for (auto it = headers.begin(); it != headers.end(); ++it) {
        result += it->first + ": " + it->second + "\r\n";
    }

    return result;
}