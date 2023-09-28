#include "functions.hpp"
#include <iomanip>
#include <iostream>
#include <regex>

#define NUM_MASK IP.substr(IP.find_first_of('/', 0) + 1, IP.length() - IP.find_first_of('/', 0))

int main(int argc, char **argv) {
    // argv[0] is directory
    // argv[1] is the input IP address

    // IP validation regex
    std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(?:/[1-2]\\d|/3[0-1]|/[1-9])?");
    std::string IP = argv[1];

    //  no arguments
    if (argc < 2) {
        std::cout << "No IP Address provided!" << std::endl;
        return -1;
    }

    //  too many arguments
    else if (argc > 2) {
        std::cout << "Too much data provided!" << std::endl;
    }

    //  invalid regex check
    else if (!(std::regex_match(IP, ipv4))) {
        std::cout << "Invalid IP address!" << std::endl;
    }

    //  TODO: fix cout formatting, fix wildcard function (reverseOctet) functionalities: network, broadcast, host min, host max, hosts/net

    //  without providing network mask
    else if (IP.find_first_of('/', 0) == IP.npos) {
        std::cout << std::right << "Address: " + IP << std::setw(13) << " " << std::setw(1) << Functions::ipToBits(IP) << std::endl;
    }

    else {
        std::cout << std::right << "Address: " + IP.substr(0, IP.find_first_of('/', 0)) << std::setw(13) << " " << std::setw(1) << Functions::ipToBits(IP) << std::endl;
        std::cout << std::right << "Netmask: " + Functions::getNetmask(std::stoi(NUM_MASK)) + " = " + NUM_MASK << std::setw(13) << " " << std::setw(1) << Functions::ipToBits(Functions::getNetmask(std::stoi(NUM_MASK))) << std::endl;
        std::cout << std::right << "Wildcard: " + Functions::getWildcard(std::stoi(NUM_MASK)) << std::setw(13) << " " << std::setw(1) << Functions::ipToBits(Functions::getWildcard(std::stoi(NUM_MASK))) << std::endl;
    }

    return 0;
}