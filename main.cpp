#include <iostream>
#include <regex>
#include "functions.hpp"

int main(int argc, char **argv)
{
    // argv[0] is directory
    // argv[1] is the input IP address

    // IP validation regex
    std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    std::string IP = argv[1];

    //  no arguments
    if (argc < 2)
    {
        std::cout << "No IP Address provided!" << std::endl;
        return -1;
    }

    //  too many arguments
    else if (argc > 2)
    {
        std::cout << "Too much data provided!" << std::endl;
    }

    //  invalid regex check
    else if (!(std::regex_match(IP, ipv4)))
    {
        std::cout << "Invalid IP address!" << std::endl;
    }

    //  TODO: all ipcalc functionalities, text formatting (cout formatting), possibility of checking the mask, etc.
    else
    {
        std::cout << "Address: " << IP << "\n";
        std::cout << " Bitwise Representation: " << ipToBits(IP) << std::endl;
    }

    return 0;
}