#include "headers.h"

#include <ctime>

// Headers set method
void HTTP::Headers::set(std::string key, std::string value) {
    headers[key] = value;
}

// Headers get method
std::string HTTP::Headers::get(std::string key) const {
    return headers.at(key);
}

// Headers to_string method
std::string HTTP::Headers::to_string() {
    std::string result = "";

    for (auto it = headers.begin(); it != headers.end(); ++it) {
        result += it->first + ": " + it->second + "\r\n";
    }

    result += "\r\n";

    return result;
}

std::string HTTP::Headers::get_date_formatted() {
    std::time_t time;
    std::time(&time);

    auto gmt = std::gmtime(&time);

    size_t length;
    char buffer[80];

    length = strftime(buffer, 80, "%a, %d %b %G %T GMT", gmt);

    return std::string{ buffer, buffer + length };
}

// Headers has method
bool HTTP::Headers::has(std::string key) const {
    return headers.find(key) != headers.end();
}