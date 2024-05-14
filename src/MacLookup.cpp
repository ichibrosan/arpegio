//
// Created by doug on 5/12/24.
//

#include "MacLookup.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <curl/curl.h> // Make sure to link with -lcurl
#include "../include/urlencode.h"

MacLookup::MacLookup() {
    loadLocalDatabase();
}

void MacLookup::loadLocalDatabase() {
    std::ifstream file("data/known_hosts.txt");
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string mac, manufacturer;
        if (getline(iss, mac, ',') && getline(iss, manufacturer)) {
            localMacDatabase[mac] = manufacturer;
        }
    }
}

std::string MacLookup::lookupManufacturerLocal(const std::string& macAddress) {
    auto it = localMacDatabase.find(macAddress);
    if (it != localMacDatabase.end()) {
        return it->second;
    }
    return "Unknown";
}

std::string MacLookup::lookupManufacturerWeb(const std::string& macAddress) {
    return fetchManufacturerFromWeb(macAddress);
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string MacLookup::fetchManufacturerFromWeb(const std::string& macAddress) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://api.macvendors.com/" + urlencode(macAddress);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
		sleep(1);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return "Unknown";
        }
        return readBuffer;
    }
    return "Unknown";
}

