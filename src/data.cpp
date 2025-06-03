#include "data.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace DATA {
   

std::vector<std::string> readFromFile(std::string& filePath){

   // Essa função basicamente lê uma arquivo (filePath) e retorna um vetor com todas as suas palavras


   std::vector<std::string> words;
   std::ifstream file(filePath);
   std::string word;

   if (!file.is_open()){
      std::cerr << "Erro ao abrir o arquivo"<< filePath << std::endl;
      return words; 
   }

   while(file >> word){
      words.push_back(word);
   }

   file.close();
   return words;

}

std::vector<FileData>* readFiles(int amount){

   // Essa função recebe um inteiro positivo que dita quantos arquivos serão lidos
   // A função lê cada um dos arquivos X.txt e para cada arquivo cria um objeto FileData
   // onde serão armazenados o ID do arquivo e um vetor com suas palavras
   // Tudo isso ao final é armazenado no vetor files e retornado

   std::vector<FileData>* files = new std::vector<FileData>;

   for (int i = 0; i <= amount; ++i){
      std::string filePath = "..\\data\\" + std::to_string(i) + ".txt";
      std::vector<std::string> words = readFromFile(filePath);
      FileData* file = new FileData;
      file->fileID = i;
      file->words = words;
      files->push_back(*file);
   }
   return files;
}


}
