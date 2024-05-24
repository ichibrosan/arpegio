// MacAddr2DNS.cpp 2024/05/23 dwg -
// Copyright (c) 2024 Douglas Goodall. All Rights Reserved.

// Created by doug on 5/23/24.


#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <curl/curl.h> // Make sure to link with -lcurl
#include "../include/urlencode.h"
#include "../include/MacAddr2DNS.h"

MacAddr2DNS::MacAddr2DNS() {
    std::cout << __FUNCTION__ << " called" << std::endl;
    loadLocalDatabase();
}

void MacAddr2DNS::loadLocalDatabase() {
    std::ifstream file("../data/macaddr2dns.txt");
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string mac, dnsname;
        if (getline(iss, mac, ',') &&
            getline(iss, dnsname)) {
            std::cout << __FUNCTION__ << ": mac: " << mac;
            std::cout <<                  " dns: " << dnsname << std::endl;
            localDNSDatabase[mac] = dnsname;
            std::cout << "localDNSDatabase[mac] is "
                      <<  localDNSDatabase[mac] << std::endl;
        }
    }
}

std::string MacAddr2DNS::lookupLocalDNS(
        const std::string& macAddress) {
    std::cout << __FUNCTION__ << ": " << macAddress << std::endl;

    return localDNSDatabase[macAddress];

//    auto it = localDNSDatabase.find(macAddress);
//    if (it != localDNSDatabase.end()) {
//        return it->second;
//    }
//    return "Unknown";
}



///**
// * Callback function to write data read by libcurl
// * @param contents
// * @param size
// * @param nmemb
// * @param userp
// * @return
// */
//size_t WriteCallback(void *contents,
//                     size_t size,
//                     size_t nmemb,
//                     void *userp) {
//    ((std::string*)userp)->append((char*)contents, size * nmemb);
//    return size * nmemb;
//}

