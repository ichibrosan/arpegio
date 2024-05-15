//
// Created by doug on 5/12/24.
//

/**
 * This file consists of two core functions intended for validating and
 * cleaning text files which conform to the `hosts` file format (mapping
 * of IP addresses to hostnames).
 */

#include <fstream>
#include <string>
#include <regex>
#include <iostream>

#include "../include/cleanHostsFile.h"

/**
 * This is a helper function that checks if a given `line` from a hosts
 * file is valid.
 * @param line | This is a line from the hosts file
 * @return Returns `true` if the line matches a regex pattern indicating
 * a valid hosts file entry (an IP address followed by one or more
 * hostnames). Otherwise, it returns `false`.
 */
bool isValidHostsEntry(const std::string& line)
{
    std::regex hostsEntryPattern(R"(^(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})\s([\w\.-]+)(\s[\w\.-]+)*$)");
    if(std::regex_match(line, hostsEntryPattern))
        return true;

    // Return false if line does not match the pattern
    return false;
}

/**
 * This function reads a file named "generated_hosts.txt" line by line,
 * validates each line using the function
 * isValidHostsEntry(const std::string& line), and if a line is valid,
 * it gets written to another file named "clean_hosts.txt".
 */
void cleanHostsFile()
{
    std::ifstream inputFile("generated_hosts.txt");
    std::ofstream outputFile("clean_hosts.txt");
    std::string line;

    if (inputFile.is_open() && outputFile.is_open()) {
        while (getline(inputFile, line)) {
            if (isValidHostsEntry(line)) {
                std::cout << __FUNCTION__ << ": " << line << std::endl;
                outputFile << line << std::endl;
            }
        }
    }
    else {
        std::cerr << "Failed to open file!";
    }
}