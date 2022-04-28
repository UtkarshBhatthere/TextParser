#include <iostream>
#include <fstream>
#include "parser.h"

std::string assetPath = "../assets";


int main() {
    
    std::fstream file(assetPath + "/test.txt");
    parser parserObj(file);
    std::cout << parserObj.word_stat() << "\n";
}