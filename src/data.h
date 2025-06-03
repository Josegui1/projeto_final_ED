#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <vector>

struct FileData{
   int fileID;
   std::vector<std::string> words;
};

namespace DATA {
std::vector<std::string> readFromFile(std::string& fileName);
std::vector<FileData>* readFiles(int amount);

}

#endif