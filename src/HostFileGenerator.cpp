//
// Created by doug on 5/12/24.
//

/**
 * This file consists of two core functions, which are member functions of
 * `class HostFileGenerator`. The main purpose of the class is to generate
 * and clean a `hosts` file format text file (mapping of IP addresses to
 * hostnames) from a given set of nodes.
 */

#include "HostFileGenerator.h"
#include <fstream>
#include <iostream>
#include "../include/cleanHostsFile.h"

/**
 * This function generates a host file named "generated_hosts.txt" from a
 * given list of nodes. After generating the file, it calls the
 * cleanHostsFile() function from "cleanHostsFile.h" to clean the generated
 * file.
 * @param nodes | Vector of Node objects to be written to the hosts file.
 */
void HostFileGenerator::generateHostFile(const std::vector<Node>& nodes) {
    std::ofstream outFile("generated_hosts.txt");
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    outFile << "# Generated Hosts File\n";
    for (const auto& node : nodes) {
//        std::cout << __FUNCTION__
//                  << ": "
//                  << formatHostEntry(node)
//                  << std::endl;
        outFile << formatHostEntry(node) << std::endl;
    }

    outFile.close();
    std::cout << "Hosts file generated successfully at 'generated_hosts.txt'"
    << std::endl;
	cleanHostsFile();
	std::cout << "Hosts file cleaned" << std::endl;
}

/**
 * This function formats a given node into a tab-separated string comprising
 * the node's IP address, manufacturer, and MAC address (in a comment
 * following a '#').
 * @param node | A single Node object that needs to be formatted.
 * @return A string representing the formatted node information.
 */
std::string HostFileGenerator::formatHostEntry(const Node& node) {
    //std::cout << __FUNCTION__ << ": " << node.ipAddress << std::endl;
    return  node.ipAddress + "\t" +
            node.manufacturer + "\t# " +
            node.macAddress;
}