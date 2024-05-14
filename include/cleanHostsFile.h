//
// Created by doug on 5/12/24.
//

#ifndef CLEANHOSTSFILE_H
#define CLEANHOSTSFILE_H
#include <string>

bool isValidHostsEntry(const std::string& line);

void cleanHostsFile();


#endif //CLEANHOSTSFILE_H
