#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    ifstream source(argv[1]);
    if (!source.is_open()) {
        cerr << "error opening file!" << std::endl;
        return 1; 
    }

    string line;
    while (getline(source, line)) {
        cout << line << endl;
    }
}