/**
 * @file urlencode.cpp
 * @brief Implementation of the URL Encoder
 * @author Douglas Goodall
 * @date 24th May, 2024
 * Copyright (c) 2024 Douglas Goodall. All Rights Reserved.
 * */

// Include necessary standard libraries
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

/**
 * @file Utilities.cpp
 * @brief Implement utility functions that can be used throughout the application.
 *
 * This file contains a function for URL encoding a string, often used when assembling requests to web APIs.
 * */

/**
 * @brief: This function is used for encoding a string into URL format.
 *
 * It works by replacing most non-alphanumeric characters with percent-encoded characters.
 *
 * The function would typically be used when constructing URLs programmatically, to ensure
 * they are in the correctly formatted. Incorrectly formatted URLs can lead to incorrect
 * behavior when interacting with the web server.
 *
 * @param value: The string to be URL encoded.
 * @return A string which has been URL encoded.
 */
std::string urlencode(const std::string &value) {
    // Create an output string stream
    std::ostringstream escaped;
    escaped.fill('0');
    // Set stream to output hexadecimal numbers
    escaped << std::hex;

    // Iterate over each character in the string
    for (std::string::const_iterator i = value.begin(), end = value.end(); i != end; ++i) {
        std::string::value_type c = (*i);

        // Check if current character is alphanumeric or a selected set of punctuation
        // If so, add it directly to the stream
        // This set ('-', '_', '.', '~') is safe to include in a URL without encoding
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // If current character is not safe, add its percent-encoded value to the stream
        // The percent-encoded value is made by replacing the character with a '%' character
        // followed by two hexadecimal digits corresponding to the character's ASCII value
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }

    // Return the completed URL-encoded string
    return escaped.str();
}