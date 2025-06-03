#include "data.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace DATA {
   
std::vector<std::string> readFromFile(std::string& fileName){

   std::vector<std::string> words;
   std::ifstream file(fileName);
   std::string word;

   if (!file.is_open()){
      std::cerr << "Erro ao abrir o arquivo"<< fileName << std::endl;
      return words; 
   }

   while(file >> word){
      words.push_back(word);
   }

   file.close();
   return words;

}

}
