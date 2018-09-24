#include <iostream>
#include <stdio.h>
#include "boost/filesystem.hpp" 
#include <sstream>
#include <string>
#include <fstream>
using namespace boost::filesystem;
//http://www.cplusplus.com/reference/string/string/find/| http://www.cplusplus.com/forum/beginner/33615/
int main(int argc, char **argv) {
    
    path p(".");
    std::string search;
    std::ifstream inFile;
    std::string line;
    std::cout << "Enter word to search for: ";
    std::cin >>search;
    for (auto &entry : directory_iterator(p)) {
        std::cout << entry.path().string() << is_regular_file(entry.path()) << "\n";
        

        inFile.open(entry.path().string());

        if(!inFile){
        std::cout << "Unable to open file" <<"\n";
        exit(1);
        }
        

        size_t pos;
        while(inFile.good())
        {
            getline(inFile,line); // get line from file
            pos=line.find(search); // search
            if(pos!=std::string::npos) // string::npos is returned if string is not found
                {
                    
                    std::cout <<"article:"<<entry.path().string()<<"Position" <<pos<<"\n";
                    
                }
        }
        inFile.close();
    }
    return 0;
    
}
