#ifndef FUNCTIONS_H
#define FUNCTIONS_H
// TODO: Maybe implement a class FUNCTIONS, with static functions (so octetToBits will be unavailible to main indirectly)
#include <algorithm>
#include <string>

//  convert decimal representation of octet to binary
std::string octetToBits(const std::string &octet) {
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

//  convert decimal IP to binary
std::string ipToBits(const std::string &IP) {
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

#endif