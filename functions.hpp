#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <cmath>
#include <string>

#define NUM_MASK IP.substr(IP.find_first_of('/', 0) + 1, IP.length() - IP.find_first_of('/', 0))

// Class "Functions" helps to keep encapsulation (main.cpp doesn't need octetToBits)
class Functions {

public:
    static std::string ipToBits(const std::string &IP);
    static std::string getNetmask(int mask);
    static std::string getWildcard(int mask);
    static std::string getNetwork(const std::string &IP);

    // TODO: all functions down below
    static std::string getBroadcast(const std::string &IP); // binary: wildcard OR address
    static std::string getHostMin();
    static std::string getHostMax();
    static unsigned int Hosts();

private:
    static std::string octetToBits(const std::string &octet);
    static std::string reverseOctets(const std::string &IP);
    static std::string ipBitsToDecimal(const std::string &IP);
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

    for (int i = 0; i < 35; i++) {
        if (i == 8 or i == 17 or i == 26) {
            netmask += '.';
        } else if (mask == 0) {
            netmask += '0';
        } else {
            netmask += '1';
            mask--;
        }
    }

    return ipBitsToDecimal(netmask);
}

/// @brief get wildcard address from mask number (ex. /24 => 0.0.0.255)
/// @param mask number of mask (ex. 24)
/// @return wildcard address
inline std::string Functions::getWildcard(int mask) {
    std::string wildcard = ipToBits(getNetmask(32 - mask));
    std::reverse(wildcard.begin(), wildcard.end());
    return ipBitsToDecimal(wildcard);
}

/// @brief returns IP of network in which host is
/// @param IP - address of host
/// @return address of network
inline std::string Functions::getNetwork(const std::string &IP) {
    std::string network = "";
    std::string host = Functions::ipToBits(IP.substr(0, IP.find_first_of('/', 0)));
    std::string netmask = Functions::ipToBits(Functions::getNetmask(std::stoi(NUM_MASK)));

    for (int i = 0; i < host.length(); i++) {
        if (host[i] == '.')
            network += '.';
        else if ((int(host[i]) - '0') & (int(netmask[i]) - '0'))
            network += '1';
        else
            network += '0';
    }

    return ipBitsToDecimal(network) + "/" + NUM_MASK;
}

/// @brief Transforms Binary representation of IP into decimal
/// @param IP binary decimal address
/// @return decimal IP address
inline std::string Functions::ipBitsToDecimal(const std::string &IP) {
    std::string decimal = "";
    int octetDec = 0;
    int pos = 0;
    std::string curr = "";

    for (int i = IP.length() - 1; i >= 0; i--) {
        if (IP[i] == '.') {
            decimal += std::to_string(octetDec) + '.';
            octetDec = 0;
            pos = 0;
        } else {
            curr.push_back(IP[i]);
            octetDec += pow(2, pos) * std::stoi(curr);
            curr = "";
            pos++;
        }
    }
    decimal += std::to_string(octetDec);

    return reverseOctets(decimal);
}

/// @brief reverses octets in IP address
/// @param IP IP address which will be reversed
/// @return reversed IP address
inline std::string Functions::reverseOctets(const std::string &IP) {
    std::string octet[4] = {};
    int j = 0;
    int oct = 0;

    while (oct < 4) {
        octet[oct] = IP.substr(j, IP.find_first_of('.', j) - j);
        j = IP.find_first_of('.', j) + 1;
        oct++;
    }

    return octet[3] + "." + octet[2] + "." + octet[1] + "." + octet[0];
}

#endif