#include "Scanner.h"
#include <stdlib.h>
#include "MacLookup.h"
#include "MacAddr2DNS.h"
#include "HostFileGenerator.h"
#include "Utilities.h"
#include <iostream>
#include <vector>

/**
 * This is the main entry point of the scanner application
 * @return EXIT_SUCCESS
 */
int main() {
    try {
        // Initialize the scanner and perform subnet scanning
        Scanner scanner;
        auto nodes = scanner.scanSubnet();

        // Initialize MAC address lookup
        MacLookup macLookup;
        for (auto& node : nodes) {
            node.manufacturer = macLookup.lookupManufacturerWeb(node.macAddress);
        }


        MacAddr2DNS dnsLookup;

















        // Generate /etc/hosts style file
        HostFileGenerator fileGenerator;
        fileGenerator.generateHostFile(nodes);

        // Output completion message
        std::cout << "Subnet scanning and host file generation completed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;  // Return non-zero value to indicate error
    }

    return EXIT_SUCCESS;  // Successful execution
}
