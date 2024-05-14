//
// Created by doug on 5/12/24.
//

#include "HostFileGenerator.h"
#include <fstream>
#include <iostream>
#include "../include/cleanHostsFile.h"

void HostFileGenerator::generateHostFile(const std::vector<Node>& nodes) {
    std::ofstream outFile("generated_hosts.txt");
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    outFile << "# Generated Hosts File\n";
    for (const auto& node : nodes) {
        outFile << formatHostEntry(node) << std::endl;
    }

    outFile.close();
    std::cout << "Hosts file generated successfully at 'generated_hosts.txt'" << std::endl;
	cleanHostsFile();
	std::cout << "HOsts file cleaned" << std::endl;
}

std::string HostFileGenerator::formatHostEntry(const Node& node) {
    return node.ipAddress + "\t" + node.manufacturer + "\t# " + node.macAddress;
}