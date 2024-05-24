/**
 * @file HostFileGenerator.cpp
 * @brief This file includes functions for the `HostFileGenerator` class.
 * @author Douglas Goodall
 * @date 5/12/24
 * Copyright (c) 2024 Douglas Goodall. All Rights Reserved.
 */

// Include necessary header files
#include "HostFileGenerator.h"
#include "MacAddr2DNS.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include "../include/cleanHostsFile.h"

/**
 * Generates a hosts file (../data/generated_hosts.txt) from a collection
 * of nodes.
 * @param nodes: vector of Node objects to configure the hosts file.
 * Calls the `cleanHostsFile` function to clean the generated file before
 * use.
 * Can throw a runtime_error if the file fails to open for writing.
 */
void HostFileGenerator::generateHostFile(const std::vector<Node>& nodes) {
    std::ofstream outFile("../data/generated_hosts.txt");

    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    MacAddr2DNS dnsNameProvider;
    outFile << "# Generated Hosts File\n";

    for (const auto& node : nodes) {
        outFile << formatHostEntry(node, dnsNameProvider) << std::endl;
    }

    outFile.close();
    cleanHostsFile();
}

/**
 * Formats a given node into a tab-separated string of the node's IP address,
 * hostname, and MAC address.
 * @param node: Node object to be formatted.
 * @param dnsNameProvider: Object of `MacAddr2DNS` type to lookup for
 * local DNS.
 * @return formatted string of node's data to be written in the hosts file.
 */
std::string HostFileGenerator::formatHostEntry(
        const Node& node,MacAddr2DNS& dnsNameProvider) {
    std::string hostname =
            dnsNameProvider.lookupLocalDNS(node.macAddress);
    char szRef[64];
    std::string stdTemp;

    if (hostname.length() == 0) {
        strcpy(szRef, node.macAddress.c_str());
        char szTemp[13];
        for (int i=0, j=0; i<12; i++, j++) {
            if (szRef[j] == ':') j++;
            szTemp[i] = szRef[j];
        }

        szTemp[12] = 0;
        stdTemp = szTemp;

        hostname = "node-" + stdTemp;
    }

    return  node.ipAddress + "\t" + hostname + "\t# " + node.macAddress;
}

/////////////////////////////////
// eof - HostFileGenerator.cpp //
/////////////////////////////////

