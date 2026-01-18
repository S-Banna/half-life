#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"

using namespace std;

int main(int argc, char** argv) {
    ifstream source(argv[1]);
    if (!source.is_open()) {
        cerr << "error opening file!" << std::endl;
        return 1;
    }

    string contents((istreambuf_iterator<char>(source)), istreambuf_iterator<char>());
    Lexer* tokens = new Lexer(contents);
}