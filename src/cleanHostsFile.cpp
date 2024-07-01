/**
 * @file cleanHostsFile.cpp
 * @brief This file provides validation and cleaning for files conforming to
 * the `hosts` file format.
 * @author Douglas Goodall
 * @date 2024
 * Copyright (c) 2024 Douglas Goodall. All Rights Reserved.
 */

// Include necessary libraries
#include <fstream>
#include <string>
#include <regex>
#include <iostream>
#include <string.h>
#include "../include/cleanHostsFile.h"

/**
 * Function: isValidHostsEntry
 * ----------------------------
 * This function checks if a given line from a hosts file should be included
 * in hosts.
 *
 * @param line : A string representing a line read from the hosts file.
 *
 * Following conditions are checked in the hosts file line:
 * - If it starts with "Starting"
 * - If it starts with "Ending"
 * - If it ends with "packets"
 * - If "errors" is found in the 16th character of the line
 *
 * If ANY of these conditions are met, the line is considered INVALID.
 *
 * @return Returns `true` if the line is a valid hosts entry. Otherwise,
 * returns `false`.
 */
bool isValidHostsEntry(const std::string& line) {
    // Copy the line to a character array (C-Style string) for easier
    // manipulation
    char szTemp[1024];
    strcpy(szTemp, line.c_str());

    // Check the conditions for line validity
    if(0 == strncmp("Starting",szTemp,8) || 0 == strncmp("Ending",szTemp,6)
       || 0 == strncmp("packets",&szTemp[strlen(szTemp)-7],7)
       || 0 == strncmp("errors",&szTemp[15],6)) {
        return false;
    }
    return true;
}

/**
 * Function: cleanHostsFile
 * -------------------------
 * This function reads a file named "generated_hosts.txt", validates each
 * line, and writes all the valid lines
 * to a new file named "clean_hosts.txt".
 *
 * @param none
 *
 * The file reading, validation and writing process are as follow:
 * - Open both "generated_hosts.txt" and "clean_hosts.txt" in the "../data"
 * directory
 * - If files are not open, print "Failed to open file!"
 * - Otherwise, read the input file line by line
 * - For each line, validate it with `isValidHostsEntry` function
 * - If the line is valid, write it to the output file
 * - Continue this until all lines in the input file are processed
 *
 * @return Returns nothing. The function type is void.
 */
void cleanHostsFile() {
    // File streams
    std::ifstream inputFile("../data/generated_hosts.txt");
    std::ofstream outputFile("../data/clean_hosts.txt");

    // String to hold each line
    std::string line;

    // Check if files are open
    if (inputFile.is_open() && outputFile.is_open()) {
        // Read input file line by line
        while (getline(inputFile, line)) {
            // Validate each line
            if (isValidHostsEntry(line)) {
                // Write valid lines to output file
                outputFile << line << std::endl;
            }
        }
    }
    else {
        // If files are not open, prints an error message
        std::cerr << "Failed to open file!";
    }
}

//////////////////////////////
// eof - cleanHostsFile.cpp //
//////////////////////////////