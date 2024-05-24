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
 * @return Returns `true` if the line shouold be included in hosts.
 * Otherwise, it returns `false`.
 */
bool isValidHostsEntry(const std::string& line)
{
    char szTemp[1024];
    strcpy(szTemp,line.c_str());
    //std::cout << __FUNCTION__ << " line= " << line << std::endl;
    if(0 == strncmp("Starting",szTemp,8)) {
        //std::cout << "Starting detected" << std::endl;
        return false;
    }
    if(0 == strncmp("Ending",szTemp,6)) {
        //std::cout << "Starting detected" << std::endl;
        return false;
    }
    if(0 == strncmp("packets",&szTemp[strlen(szTemp)-7],7)) {
        //std::cout << "packets detected" << std::endl;
        return false;
    }
    if(0 == strncmp("errors",&szTemp[15],6)) {
        //std::cout << "errors detected" << std::endl;
        return false;
    }

    return true;

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
                //std::cerr << "Valid hosts entry: " << line << std::endl;
                //std::cout << __FUNCTION__ << ": " << line << std::endl;
                outputFile << line << std::endl;
            }
        }
    }
    else {
        std::cerr << "Failed to open file!";
    }
}