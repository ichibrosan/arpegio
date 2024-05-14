//
// Created by doug on 5/12/24.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

class Utilities {
public:
    static std::string trim(const std::string& str);
    static std::string toUpperCase(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char delimiter);

    // Networking utilities
    static std::string formatIPAddress(const std::string& ip);
    static std::string parseMACAddress(const std::string& rawMac);
};

#endif // UTILITIES_H
