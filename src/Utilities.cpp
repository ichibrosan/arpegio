//
// Created by doug on 5/12/24.
//

#include "Utilities.h"
#include <algorithm>
#include <sstream>
#include <cctype>

// String trimming to remove leading and trailing spaces
std::string Utilities::trim(const std::string& str) {
    std::string out = str;
    out.erase(out.begin(), std::find_if(out.begin(), out.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    out.erase(std::find_if(out.rbegin(), out.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), out.end());
    return out;
}

// Convert a string to upper case
std::string Utilities::toUpperCase(const std::string& str) {
    std::string out = str;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return out;
}

// Split a string based on a delimiter
std::vector<std::string> Utilities::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

// Format an IP address, potentially useful for consistent formatting
std::string Utilities::formatIPAddress(const std::string& ip) {
    // This could be expanded with actual IP formatting logic
    return ip;
}

// Parse a MAC address to standard format
std::string Utilities::parseMACAddress(const std::string& rawMac) {
    std::string formattedMac;
    for (auto c : rawMac) {
        if (c != ':' && c != '-' && c != '.') {
            formattedMac += toUpperCase(std::string(1, c));
            if (formattedMac.length() % 3 == 2 && formattedMac.length() != 17) {
                formattedMac += ":";
            }
        }
    }
    return formattedMac;
}