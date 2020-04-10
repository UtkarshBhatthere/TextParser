#include <iostream>
#include <fstream>
#include "parser.h"


int main() {
    
    std::fstream file("test.txt");
    parser parserObj(file);
    std::cout << parserObj.word_stat() << "\n";
}