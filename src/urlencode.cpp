//
// Created by doug on 5/12/24.
//

#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

/*
 * This function is typically used when constructing URLs programmatically,
 * to ensure they are correctly format. Incorrectly formatted URLs can lead
 * to incorrect behavior when interacting with the web server.
 */

/**
 * urlencode function is used for encoding a string into URL format, by
 * replacing most non-alphanumeric characters with percent-encoded characters.
 * @param value
 * @return
 */
std::string urlencode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = value.begin(), end = value.end(); i != end; ++i) {
        std::string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}