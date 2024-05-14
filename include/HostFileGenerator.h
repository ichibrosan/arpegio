//
// Created by doug on 5/12/24.
//

#ifndef HOSTFILEGENERATOR_H
#define HOSTFILEGENERATOR_H

#include <string>
#include <vector>
#include "Scanner.h"  // Include the Scanner header for the Node struct

class HostFileGenerator {
public:
    void generateHostFile(const std::vector<Node>& nodes);

private:
    std::string formatHostEntry(const Node& node);
};

#endif // HOSTFILEGENERATOR_H
