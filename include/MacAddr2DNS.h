//
// Created by doug on 5/23/24.
//

#ifndef ARPEGIO_MACADDR2DNS_H
#define ARPEGIO_MACADDR2DNS_H

#include <string>
#include <vector>
#include <unordered_map>

class MacAddr2DNS {
public:
    MacAddr2DNS();
    void loadLocalDatabase();
    std::string lookupLocalDNS(const std::string& macAddr);
private:
    std::unordered_map<std::string, std::string> localDNSDatabase;
};


#endif //ARPEGIO_MACADDR2DNS_H
