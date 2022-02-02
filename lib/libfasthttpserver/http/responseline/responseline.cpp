#include "responseline.h"

// ResponseLine class constructor
HTTP::ResponseLine::ResponseLine(std::string version, std::string status, std::string reason) {
    this->version = version;
    this->status = status;
    this->reason = reason;
}

// ResponseLine get_version method
std::string HTTP::ResponseLine::get_version() {
    return version;
}

// ResponseLine get_status method
std::string HTTP::ResponseLine::get_status() {
    return status;
}

// ResponseLine get_reason method
std::string HTTP::ResponseLine::get_reason() {
    return reason;
}

// ResponseLine to_string method
std::string HTTP::ResponseLine::to_string() {
    return version + " " + status + " " + reason + "\r\n";
}