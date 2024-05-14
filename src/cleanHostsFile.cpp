//
// Created by doug on 5/12/24.
//

#include <fstream>
#include <string>
#include <regex>
#include <iostream>

#include "../include/cleanHostsFile.h"

bool isValidHostsEntry(const std::string& line)
{
    std::regex hostsEntryPattern(R"(^(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})\s([\w\.-]+)(\s[\w\.-]+)*$)");
    if(std::regex_match(line, hostsEntryPattern))
        return true;

    // Return false if line does not match the pattern
    return false;
}

void cleanHostsFile()
{
    std::ifstream inputFile("generated_hosts.txt");
    std::ofstream outputFile("clean_hosts.txt");
    std::string line;

    if (inputFile.is_open() && outputFile.is_open()) {
        while (getline(inputFile, line)) {
            if (isValidHostsEntry(line)) {
                outputFile << line << std::endl;
            }
        }
    }
    else {
        std::cerr << "Failed to open file!";
    }
}