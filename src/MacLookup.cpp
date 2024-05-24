/**
 * @file MacLookup.cpp
 * @brief Implementation of the MacLookup class.
 * @author Douglas Goodall
 * @date 24th May, 2024
 * Copyright (c) 2024 Douglas Goodall. All Rights Reserved.
 * The class interfaces with a file and a web service to retrieve
 * manufacturer information for a given MAC address.
 * */

#include "MacLookup.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <curl/curl.h>
#include "../include/urlencode.h"

/**
 * The constructor for MacLookup, initializes the object and loads the local
 * database.
 */
MacLookup::MacLookup() {
    loadLocalDatabase();
}

/**
 * This function opens a file ("data/known_hosts.txt") and reads it line by
 * line to load MAC address and manufacturer pairs
 * into the localMacDatabase map where the MAC address is the key and the
 * manufacturer is the value.
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
 * This function searches for the MAC address in the localMacDatabase map
 * and if found,
 * returns the corresponding manufacturer, else returns "Unknown".
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
 * This function fetches the manufacturer from the web using the
 * macvendors API.
 * It uses the macAddress as a parameter to fetch the manufacturer
 * from the API.
 */
std::string MacLookup::lookupManufacturerWeb(const std::string& macAddress) {
    std::cout << "Lookup manufacturer web: " << macAddress << std::endl;
    return fetchManufacturerFromWeb(macAddress);
}

/**
 * This function is a callback for the libcurl library. It writes data
 * read by libcurl
 * into a string object pointed by userp.
 */
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/**
 * This function interfaces with the libcurl library to fetch data from
 * macvendors API.
 * It initializes a curl object, sets necessary options, performs a request
 * and retrieves the response.
 * In case of failure, it returns "Unknown". Else, the response received
 * is returned.
 */
std::string MacLookup::fetchManufacturerFromWeb(
        const std::string& macAddress) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if (curl) {
        // Prepare the url with the mac address
        std::string url = "https://api.macvendors.com/" +
                urlencode(macAddress);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Specify the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        // Pass the readBuffer to the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        // Pause to avoid hitting rate limits
        sleep(1);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            return "Unknown";
        }
        // Return the response
        return readBuffer;
    }
    return "Unknown";
}

/////////////////////////
// eof - MacLookup.cpp //
/////////////////////////