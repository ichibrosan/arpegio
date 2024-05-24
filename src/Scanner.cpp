/**
 * @file Scanner.cpp
 * @brief Implementation of scanner functionality.
 * @author Douglas Goodall
 * @date 24th May, 2024
 * Copyright (c) 2024 Douglas Goodall. All Rights Reserved.
 */

// Includes necessary header files
#include "Scanner.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <array>
#include <memory>
#include <cstdio>
#include <cstring>

/**
 * @file Scanner.cpp
 * @brief Implementation of the Scanner class.
 * @author Douglas Goodall
 * @date 24th May, 2024
 * The class is responsible for subnet scanning, executing Linux commands and parsing their results.
 * */

// The constructor of the Scanner class. It doesn't need to perform any extra
// operations for now.
Scanner::Scanner() {}

/**
 * @brief: This method runs an arp-scan on the local subnet, parses the output and returns a list of nodes (or hosts).
 * @return: vector of Node structures, each representing a host on the network.
 */
std::vector<Node> Scanner::scanSubnet() {
    std::vector<Node> nodes;
    std::string arpScanResult = executeCommand("arp-scan --localnet");
    parseArpResult(arpScanResult, nodes);
    return nodes;
}

/**
 * @brief: This function executes a given Linux shell command and returns the standard output.
 * @param cmd: A string containing the Linux command to be executed.
 * @return a string containing the standard output of the executed command.
 */
std::string Scanner::executeCommand(const std::string& cmd) {
    std::cout << cmd << std::endl;
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

    // Throw a runtime error if the pipe fails.
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        std::cout << "buffer.data() is " << buffer.data();
        result += buffer.data();
    }

    return result;
}

/**
 * @brief: This function parses the output of arp-scan and populates a list of nodes.
 * @param result: a string containing the standard output of arp-scan.
 * @param nodes: a vector of Node structures to be populated.
 */
void Scanner::parseArpResult(const std::string& result, std::vector<Node>& nodes) {
    std::istringstream iss(result);
    std::string line;

    // Parse the output line by line
    while (std::getline(iss, line)) {
        // Simple filter to exclude headers
        if (line.find("Interface:") == std::string::npos) {
            std::istringstream ls(line);
            Node node;

            // If the line has an IP Address and Mac Address, create a node and add it to the vector of nodes.
            if (ls >> node.ipAddress >> node.macAddress) {
                nodes.push_back(node);
            }
        }
    }
}

///////////////////////
// eof - Scanner.cpp //
///////////////////////
