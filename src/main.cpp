#include "Scanner.h"
#include "MacLookup.h"
#include "HostFileGenerator.h"
#include "Utilities.h"
#include <iostream>
#include <vector>

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

        // Generate /etc/hosts style file
        HostFileGenerator fileGenerator;
        fileGenerator.generateHostFile(nodes);

        // Output completion message
        std::cout << "Subnet scanning and host file generation completed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;  // Return non-zero value to indicate error
    }

    return 0;  // Successful execution
}
