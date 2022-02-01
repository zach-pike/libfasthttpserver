#pragma once

#include <map>
#include <string>

class Headers {
    private:
        std::map<std::string, std::string> headers;

    public:
        void set(std::string key, std::string value);
        std::string get(std::string key);

        std::string to_string();
};