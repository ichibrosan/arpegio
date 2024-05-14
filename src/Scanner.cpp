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

Scanner::Scanner() {
    // Constructor could initialize network interfaces or configurations if necessary
}

std::vector<Node> Scanner::scanSubnet() {
    std::vector<Node> nodes;
    std::string arpScanResult = executeCommand("arp-scan --localnet");
    parseArpResult(arpScanResult, nodes);
    return nodes;
}

std::string Scanner::executeCommand(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void Scanner::parseArpResult(const std::string& result, std::vector<Node>& nodes) {
    std::istringstream iss(result);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.find("Interface:") == std::string::npos) { // Simple filter to exclude headers
            std::istringstream ls(line);
            Node node;
            if (ls >> node.ipAddress >> node.macAddress) {
                nodes.push_back(node);
            }
        }
    }
}

