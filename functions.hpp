#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <cmath>
#include <string>

// Class "Functions" helps to keep encapsulation (main.cpp doesn't need octetToBits)
class Functions {

public:
    static std::string ipToBits(const std::string &IP);
    static std::string getNetmask(int mask);
    static std::string getWildcard(int mask);

private:
    static std::string octetToBits(const std::string &octet);
    static std::string reverseOctets(const std::string &IP);
};

/// @brief converts decimal representation of octet to binary
/// @param octet decimal form of octet
/// @return binary form of octet
inline std::string Functions::octetToBits(const std::string &octet) {
    int _octet = std::stoi(octet);
    std::string bits = "";
    while (_octet > 0) {
        if (_octet == 1) {
            bits.push_back('1');
            break;
        } else if (_octet % 2)
            bits.push_back('1');
        else
            bits.push_back('0');

        _octet /= 2;
    }

    std::reverse(bits.begin(), bits.end());

    while (bits.length() < 8)
        bits = '0' + bits;

    return bits;
}

/// @brief converts decimal IP to binary
/// @param IP decimal form of IP address
/// @return binary form of IP address
inline std::string Functions::ipToBits(const std::string &IP) {
    std::string bits = "";
    int i = 0;
    int dot = 0;
    while (i < IP.length()) {
        if ((dot = IP.find_first_of('.', i)) == -1) {
            bits = bits + octetToBits(IP.substr(i, IP.length() - i));
            break;
        }
        bits = bits + octetToBits(IP.substr(i, dot - i)) + '.';
        i = dot + 1;
    }
    return bits;
}

/// @brief get netmask address from mask number (ex. /24 => 255.255.255.0)
/// @param mask number of mask (ex. 24)
/// @return netmask address (ex. 255.255.255.0)
inline std::string Functions::getNetmask(int mask) {
    std::string netmask = "";
    int currOctet = 0;
    while (mask > 0) {
        if (mask >= 8) {
            netmask += "255.";
            mask -= 8;
            currOctet++;
        } else {
            netmask += std::to_string(pow(2, mask)) + ".";
            currOctet++;
            break;
        }
    }

    while (currOctet < 4) {
        netmask += "0.";
        currOctet++;
    }

    netmask.pop_back();

    return netmask;
}

/// @brief get wildcard address from mask number (ex. /24 => 0.0.0.255)
/// @param mask number of mask (ex. 24)
/// @return wildcard address
inline std::string Functions::getWildcard(int mask) {
    std::string wildcard = getNetmask(32 - mask);
    return reverseOctets(wildcard);
}

/// @brief reverses octets in IP address
/// @param IP IP address which will be reversed
/// @return reversed IP address
inline std::string Functions::reverseOctets(const std::string &IP) {
    std::string octet[4] = {};
    int j = 0;
    // int dot = 0;

    for (int i = 0; i < IP.length(); i++) {
        octet[j] = IP.substr(i, IP.find_first_of('.', i) - i);
        i = IP.find_first_of('.', i);
        j++;
    }

    return octet[3] + octet[2] + octet[1] + octet[0];
}

#endif