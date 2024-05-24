/**
 * @file main.cpp
 * @brief Main Entry Point
 * @author Douglas Goodall
 * @date 24th May, 2024
 * Copyright (c) 2024 Douglas Goodall. All Rights Reserved.
 * The class interfaces with a file and a web service to retrieve
 * manufacturer information for a given MAC address.
 * */


// Include necessary header files
#include "Scanner.h"
#include <stdlib.h>
#include "MacLookup.h"
#include "MacAddr2DNS.h"
#include "HostFileGenerator.h"
#include "Utilities.h"
#include <iostream>
#include <vector>

/**
 * @file main.cpp
 * @brief Main entry point for the scanner application.
 * The application scans a subnet for nodes, retrieves manufacturer
 * information for each node,
 * generates a DNS lookup and finally creates a host file.
 */

/**
 * The main function of the scanner application.
 * @return an integer status code. It returns EXIT_SUCCESS (usually 0) for
 * successful execution and EXIT_FAILURE in case of an error.
 * The latter is typically done when catching and handling an exception.
 */
int main() {
    try {
        // Initialize an instance of the Scanner class. This will perform a
        // subnet scan.
        Scanner scanner;
        auto nodes = scanner.scanSubnet();

        // Initialize an instance of the MacLookup class. This will enable
        // retrieval of manufacturer information for each node in the subnet.
        MacLookup macLookup;
        for (auto& node : nodes) {
            node.manufacturer =
                    macLookup.lookupManufacturerWeb(node.macAddress);
        }

        // Initialize an instance of the MacAddr2DNS class. This will enable
        // DNS lookup for each node in the subnet.
        MacAddr2DNS dnsLookup;

        // Initialize an instance of the HostFileGenerator class.
        // This will enable the generation of a host file in the
        // /etc/hosts style.
        HostFileGenerator fileGenerator;
        fileGenerator.generateHostFile(nodes);

        // Output a friendly completion message to standard output
        // (typically continuing in the console or terminal window).
        std::cout << "Subnet scanning and host file generation completed "
                     "successfully." << std::endl;
    }
        // Capture and handle any exceptions that may arise.
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;  // Indicate an error occurred by returning
        // EXIT_FAILURE (typically 1).
    }
    // If no exceptions were thrown and the try block completed successfully,
    // return EXIT_SUCCESS (typically 0).
    return EXIT_SUCCESS;
}

////////////////////
// eof - main.cpp //
////////////////////
