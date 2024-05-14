//
// Created by doug on 5/12/24.
//

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

// Structure to hold node information
struct Node {
    std::string ipAddress;
    std::string macAddress;
	std::string manufacturer;
};

class Scanner {
public:
    Scanner();
    std::vector<Node> scanSubnet();

private:
    std::string executeCommand(const std::string& cmd);
    void parseArpResult(const std::string& result, std::vector<Node>& nodes);
};

#endif // SCANNER_H
