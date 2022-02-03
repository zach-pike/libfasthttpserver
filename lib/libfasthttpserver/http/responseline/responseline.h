#pragma once

#include <string>

namespace HTTP {
    class ResponseLine {
    private:
        std::string version;
        std::string status;
        std::string reason;
    public:
        ResponseLine(std::string version, std::string status, std::string reason);

        // Get part of the response line
        std::string get_version();
        std::string get_status();
        std::string get_reason();
        
        // Format the response line into a string
        std::string to_string();
    };
}