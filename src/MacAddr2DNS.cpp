/**
 * @file MacAddr2DNS.cpp
 * @brief Provides implementation for resolving MAC addresses into DNS names.
 * @author Douglas Goodall
 * @date 23rd May, 2024
 */

// Necessary inclusions
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <curl/curl.h> // Make sure to link with -lcurl
#include "../include/urlencode.h"
#include "../include/MacAddr2DNS.h"

/**
 * Default constructor for MacAddr2DNS. It calls the loadLocalDatabase
 * function upon instantiation.
 */
MacAddr2DNS::MacAddr2DNS() {
    loadLocalDatabase();
}

/**
 * Function to load the local database of MAC addresses and their
 * corresponding DNS names.
 * The database is loaded from the macaddr2dns.txt file. Each line should
 * contain a MAC address and DNS name, comma-separated.
 * The function stores the data in the localDNSDatabase map for fast lookup.
 */
void MacAddr2DNS::loadLocalDatabase() {
    std::ifstream file("../data/macaddr2dns.txt");

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);

        std::string mac, dnsname;
        if (getline(iss, mac, ',') &&
        getline(iss, dnsname)) {
            localDNSDatabase[mac] = dnsname;
        }
    }
}

/**
 * Function to lookup a given MAC address in the local database and provide
 * the corresponding DNS name.
 * @param  macAddress The MAC address to be looked up.
 * @return If found, returns the corresponding DNS name. Otherwise, returns
 * an empty string.
 */
std::string MacAddr2DNS::lookupLocalDNS(const std::string& macAddress) {
    if (localDNSDatabase.count(macAddress) > 0) {
        return localDNSDatabase[macAddress];
    } else {
        return "";
    }
}

///////////////////////////
// eof - MacAddr2DNS.cpp //
///////////////////////////