//
// Created by doug on 5/12/24.
//

#ifndef MACLOOKUP_H
#define MACLOOKUP_H

#include <string>
#include <unordered_map>

class MacLookup {
public:
    MacLookup();
    std::string lookupManufacturerLocal(const std::string& macAddress);
    std::string lookupManufacturerWeb(const std::string& macAddress);

private:
    std::unordered_map<std::string, std::string> localMacDatabase;
    void loadLocalDatabase();
    std::string fetchManufacturerFromWeb(const std::string& macAddress);
};

#endif // MACLOOKUP_H
