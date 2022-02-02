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
        std::string get_version();
        std::string get_status();
        std::string get_reason();

        std::string to_string();
    };
}