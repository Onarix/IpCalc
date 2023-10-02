#include "functions.hpp"
#include <iomanip>
#include <iostream>
#include <regex>

#define NUM_MASK IP.substr(IP.find_first_of('/', 0) + 1, IP.length() - IP.find_first_of('/', 0))
#define TEXT_WIDTH std::setw(40)

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

    //  without providing network mask
    else if (IP.find_first_of('/', 0) == IP.npos) {
        std::cout << std::right << "Address: " + IP << std::setw(13) << " " << std::setw(1) << Functions::ipToBits(IP) << std::endl;
    }

    else {
        std::cout << std::left << TEXT_WIDTH << "Address: " + IP.substr(0, IP.find_first_of('/', 0)) << std::right << std::setw(1) << Functions::ipToBits(IP) << std::endl;
        std::cout << std::left << TEXT_WIDTH << "Netmask: " + Functions::getNetmask(std::stoi(NUM_MASK)) + " = " + NUM_MASK << std::right << std::setw(1) << Functions::ipToBits(Functions::getNetmask(std::stoi(NUM_MASK))) << std::endl;
        std::cout << std::left << TEXT_WIDTH << "Wildcard: " + Functions::getWildcard(std::stoi(NUM_MASK)) << std::setw(1) << Functions::ipToBits(Functions::getWildcard(std::stoi(NUM_MASK))) << std::endl;
        std::cout << std::left << "=>" << std::endl;
        std::cout << std::left << TEXT_WIDTH << "Network: " + Functions::getNetwork(IP) << std::setw(1) << Functions::ipToBits(Functions::getNetwork(IP)) << std::endl;
        std::cout << std::left << TEXT_WIDTH << "Broadcast: " + Functions::getBroadcast(IP) << std::setw(1) << Functions::ipToBits(Functions::getBroadcast(IP)) << std::endl;
        std::cout << std::left << TEXT_WIDTH << "Host min: " + Functions::getHostMin(IP) << std::setw(1) << Functions::ipToBits(Functions::getHostMin(IP)) << std::endl;
        std::cout << std::left << TEXT_WIDTH << "Host max: " + Functions::getHostMax(IP) << std::setw(1) << Functions::ipToBits(Functions::getHostMax(IP)) << std::endl;
        std::cout << std::left << "Hosts/Net: " << Functions::Hosts(std::stoi(NUM_MASK)) << std::endl;
    }

    return 0;
}