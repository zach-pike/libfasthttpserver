#pragma once

#include <map>
#include <string>

namespace HTTP {
    class Headers {
    private:
        std::map<std::string, std::string> headers;

    public:
        // Set a header
        void set(std::string key, std::string value);

        // Get a header
        std::string get(std::string key) const;

        // Check if a header exists
        bool has(std::string key) const;

        // Get formmated string of all headers
        std::string to_string();

        // Get UTC formatted date for the header "Date"
        static std::string get_date_formatted();
};
}