// Created by doug on 5/12/24.
//
#include "HostFileGenerator.h"
#include "MacAddr2DNS.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include "../include/cleanHostsFile.h"

void HostFileGenerator::generateHostFile(const std::vector<Node>& nodes) {
    std::cout << __FUNCTION__ << " running" << std::endl;
    std::ofstream outFile("generated_hosts.txt");
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    } else {
        std::cout << __FILE__ << ":" << __FUNCTION__ << " is open for writing" << std::endl;
    }

    // Instantiate MacAddr2DNS
    MacAddr2DNS dnsNameProvider;

    outFile << "# Generated Hosts File\n";
    for (const auto& node : nodes) {
        outFile << formatHostEntry(node, dnsNameProvider) << std::endl;
    }

    outFile.close();
    std::cout << "Hosts file generated successfully at 'generated_hosts.txt'"
              << std::endl;
    cleanHostsFile();
    std::cout << "Hosts file cleaned" << std::endl;
}

std::string HostFileGenerator::formatHostEntry(const Node& node, MacAddr2DNS& dnsNameProvider) {
    char szTemp[64];
    char szRef[64];
    std::string stdTemp;

    auto hostname = dnsNameProvider.lookupLocalDNS(node.macAddress); // use lookupLocalDNS here
    std::cout << __FUNCTION__ << " says hostname is " << hostname << std::endl;
//    if(0 == strncmp("Unknown",hostname.c_str(),8)) {
      if(hostname.length() == 0) {
        strcpy(szRef,node.macAddress.c_str());
        szTemp[0] = szRef[0];
        szTemp[1] = szRef[1];

        szTemp[2] = szRef[3];
        szTemp[3] = szRef[4];

        szTemp[4] = szRef[6];
        szTemp[5] = szRef[7];

        szTemp[6] = szRef[9];
        szTemp[7] = szRef[10];

        szTemp[8] = szRef[12];
        szTemp[9] = szRef[13];

        szTemp[10] = szRef[15];
        szTemp[11] = szRef[16];

        szTemp[12] = 0;
        stdTemp = szTemp;
          hostname = "node-" + stdTemp;
        std::cout << __FUNCTION__ << " says new hostname is " << hostname << std::endl;
    }
    return  node.ipAddress + "\t" +
            hostname + "\t# " +
            node.macAddress;
}



////
//// Created by doug on 5/12/24.
////
//
///**
// * This file consists of two core functions, which are member functions of
// * `class HostFileGenerator`. The main purpose of the class is to generate
// * and clean a `hosts` file format text file (mapping of IP addresses to
// * hostnames) from a given set of nodes.
// */
//
//#include "HostFileGenerator.h"
//#include <fstream>
//#include <iostream>
//#include "../include/cleanHostsFile.h"
//
///**
// * This function generates a host file named "generated_hosts.txt" from a
// * given list of nodes. After generating the file, it calls the
// * cleanHostsFile() function from "cleanHostsFile.h" to clean the generated
// * file.
// * @param nodes | Vector of Node objects to be written to the hosts file.
// */
//void HostFileGenerator::generateHostFile(const std::vector<Node>& nodes) {
//    std::ofstream outFile("generated_hosts.txt");
//    if (!outFile.is_open()) {
//        throw std::runtime_error("Failed to open file for writing.");
//    }
//
//    outFile << "# Generated Hosts File\n";
//    for (const auto& node : nodes) {
////        std::cout << __FUNCTION__
////                  << ": "
////                  << formatHostEntry(node)
////                  << std::endl;
//        outFile << formatHostEntry(node) << std::endl;
//    }
//
//    outFile.close();
//    std::cout << "Hosts file generated successfully at 'generated_hosts.txt'"
//    << std::endl;
//	cleanHostsFile();
//	std::cout << "Hosts file cleaned" << std::endl;
//}
//
///**
// * This function formats a given node into a tab-separated string comprising
// * the node's IP address, manufacturer, and MAC address (in a comment
// * following a '#').
// * @param node | A single Node object that needs to be formatted.
// * @return A string representing the formatted node information.
// */
//std::string HostFileGenerator::formatHostEntry(const Node& node) {
//    //std::cout << __FUNCTION__ << ": " << node.ipAddress << std::endl;
//    return  node.ipAddress + "\t" +
//            node.manufacturer + "\t# " +
//            node.macAddress;
//}