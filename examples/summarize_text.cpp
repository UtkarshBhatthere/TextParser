#include <iostream>
#include <fstream>
#include "parser.h"
#include <unistd.h>

int main() {

    std::string root_dir = ROOT;
    
    std::fstream file(root_dir + "/assets/test.txt");
    if (file.is_open()) {
        parser parserObj(file);
        std::cout << parserObj.word_stat() << "\n";   
    } else {
        std::cout << "Failed to open file" << std::endl;
    }

}