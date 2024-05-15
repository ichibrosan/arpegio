//
// Created by doug on 5/12/24.
// Updated by Doug on 5/14/24.  Added comments.
//

#include "MacLookup.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <curl/curl.h> // Make sure to link with -lcurl
#include "../include/urlencode.h"

// Constructor
// Loads the local database upon instantiation
/**
 * Class constructor
 */
MacLookup::MacLookup() {
    loadLocalDatabase();
}

/**
 * Load geographic data from local database (known_hosts.txt)
 * The data is used to map MAC addresses to manufacturers.
 */
void MacLookup::loadLocalDatabase() {
    std::ifstream file("data/known_hosts.txt");
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string mac, manufacturer;
        if (getline(iss, mac, ',') &&
            getline(iss, manufacturer)) {
            localMacDatabase[mac] = manufacturer;
        }
    }
}

/**
 * Lookup the manufacturer using the local database
 * @param macAddress
 * @return "Unknown" in case the MAC address is not found
 */
std::string MacLookup::lookupManufacturerLocal(
        const std::string& macAddress) {
    std::cout << "Lookup manufacturer local:  " << macAddress << std::endl;
    auto it = localMacDatabase.find(macAddress);
    if (it != localMacDatabase.end()) {
        return it->second;
    }
    return "Unknown";
}

/**
 * Lookup the manufacturer using a web service (macvendors.com)
 * @param macAddress
 * @return "Unknown" in case the MAC address is not found
 */
std::string MacLookup::lookupManufacturerWeb(
        const std::string& macAddress) {
    std::cout << "Lookup manufacturer web: " << macAddress << std::endl;
    return fetchManufacturerFromWeb(macAddress);
}

/**
 * Callback function to write data read by libcurl
 * @param contents
 * @param size
 * @param nmemb
 * @param userp
 * @return
 */
size_t WriteCallback(void *contents,
                     size_t size,
                     size_t nmemb,
                     void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/**
 * Utility function to fetch manufacturer data from the web using libcurl
 * @param macAddress
 * @return "Unknown" in case the libcurl operation fails
 */
std::string MacLookup::fetchManufacturerFromWeb(
        const std::string& macAddress) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://api.macvendors.com/" +
                          urlencode(macAddress);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        sleep(1);

        if (res != CURLE_OK) {
            fprintf(stderr,
                    "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            return "Unknown";
        }
        return readBuffer;
    }
    return "Unknown";
}