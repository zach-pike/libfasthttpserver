#include "responseline.h"

// ResponseLine class constructor
ResponseLine::ResponseLine(std::string version, std::string status, std::string reason) {
    this->version = version;
    this->status = status;
    this->reason = reason;
}

// ResponseLine get_version method
std::string ResponseLine::get_version() {
    return version;
}

// ResponseLine get_status method
std::string ResponseLine::get_status() {
    return status;
}

// ResponseLine get_reason method
std::string ResponseLine::get_reason() {
    return reason;
}

// ResponseLine to_string method
std::string ResponseLine::to_string() {
    return version + " " + status + " " + reason + "\r\n";
}