#pragma once

#include <map>
#include <string>

class Headers {
    private:
        std::map<std::string, std::string> headers;

    public:
        void set(std::string key, std::string value);
        std::string get(std::string key) const;

        std::string to_string();

        static std::string get_date_formatted();
};