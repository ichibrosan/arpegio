/**
 * @file Utilities.cpp
 * @author Douglas Goodall
 * @date 5/12/24
 */


// Included necessary standard libraries
#include "Utilities.h"
#include <algorithm>
#include <sstream>
#include <cctype>

/**
 * @file Utilities.cpp
 * @brief Contains utility functions for formatting and parsing string data.
 *
 * This includes functions for trimming strings, converting strings to upper
 * case, splitting strings by
 * delimiter, and parsing and formatting IP and MAC addresses.
 * */

/**
 * String trimming to remove leading and trailing spaces.
 * @param str: A string potentially having leading and trailing white spaces.
 * @return A string with leading and trailing white spaces removed.
 */
std::string Utilities::trim(const std::string& str) {
    std::string out = str;
    out.erase(out.begin(),
              std::find_if(out.begin(),
                           out.end(),
                           [](unsigned char ch) {
                               return !std::isspace(ch);
                           }));
    out.erase(std::find_if(out.rbegin(),
                           out.rend(),
                           [](unsigned char ch) {
                               return !std::isspace(ch);
                           }).base(), out.end());
    return out;
}

/**
 * Convert a string to upper case.
 * @param str: The original string which maybe in lower case or mixed case.
 * @return A string with all characters in upper case.
 */
std::string Utilities::toUpperCase(const std::string& str) {
    std::string out = str;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){
                       return std::toupper(c); });
    return out;
}

/**
 * Split a string based on a delimiter.
 * @param str: A string that should be split.
 * @param delimiter: A character by which the string is split.
 * @return A vector of strings which were separated by the delimiter.
 */
std::vector<std::string> Utilities::split(
        const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

/**
 * Format an IP address, potentially useful for consistent formatting.
 * @param ip: The original IP address string.
 * @return A well-formatted IP address string.
 */
std::string Utilities::formatIPAddress(const std::string& ip) {
    // This could be expanded with actual IP formatting logic
    return ip;
}

/**
 * Parse a MAC address to standard format.
 * @param rawMac: The original, potentially ill-formatted, MAC address string.
 * @return A well-formatted MAC address string.
 */
std::string Utilities::parseMACAddress(const std::string& rawMac) {
    std::string formattedMac;
    for (auto c : rawMac) {
        if (c != ':' && c != '-' && c != '.') {
            formattedMac += toUpperCase(std::string(1, c));
            if (formattedMac.length() % 3 == 2 &&
                formattedMac.length() != 17) {
                formattedMac += ":";
            }
        }
    }
    return formattedMac;
}

/////////////////////////
// eof - Utilities.cpp //
/////////////////////////