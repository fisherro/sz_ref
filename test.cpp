//c++ -I/opt/local/include -o test test.cpp

//Far from exhaustive tests. Just the primary use case I currently care about.

#include <iostream>
#include <fstream>
#include "sz_ref.hpp"

void read_file(sz_ref path)
{
    if (path.empty()) {
        std::cerr << "File path was empty.\n";
        return;
    }
    std::ifstream in(path.c_str());
    std::string line;
    while (std::getline(in, line))
        std::cout << line << '\n';
}

int main(int argc, char** argv)
{
    const char* ccp = "test.cpp";
    const char array[] = "test.cpp";
    std::string ss = "test.cpp";

    read_file("test.cpp");
    read_file(ccp);
    read_file(array);
    read_file(ss);
}
