//
// Created by doug on 5/12/24.
//

#include "Scanner.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <array>
#include <memory>
#include <cstdio>
#include <cstring>

// The constructor of Scanner class. It doesn't need to perform any extra
// operations for now.
Scanner::Scanner() {}

/**
 * scanSubnet method runs an arp-scan on the local subnet, parses the output
 * @return a list of nodes (or hosts)
 */
std::vector<Node> Scanner::scanSubnet() {
    std::vector<Node> nodes;
    std::string arpScanResult = executeCommand("arp-scan --localnet");
    parseArpResult(arpScanResult, nodes);
    return nodes;
}

/**
 * executeCommand method executes a shell command
 * @param cmd
 * @return the output
 */
std::string Scanner::executeCommand(const std::string& cmd) {
    std::cout << cmd << std::endl;
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)>
            pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(),
                 buffer.size(),
                 pipe.get()) != nullptr) {
        std::cout << "buffer.data() is " << buffer.data();
        result += buffer.data();
    }
    return result;
}

/**
 * parseArpResult method parses the output of arp-scan and populates a list
 * of nodes
 * @param result
 * @param nodes
 */
void Scanner::parseArpResult(
        const std::string& result,
        std::vector<Node>& nodes) {
    std::istringstream iss(result);
    std::string line;
    while (std::getline(iss, line)) {
        // Simple filter to exclude headers
        if (line.find("Interface:") == std::string::npos) {
            std::istringstream ls(line);
            Node node;
            if (ls >> node.ipAddress >> node.macAddress) {
                nodes.push_back(node);
            }
        }
    }
}