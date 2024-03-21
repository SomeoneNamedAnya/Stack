#include <iostream>
#include "processor.h"

int main(){

    while (true) {
        std::cout << "put link:\n";
        std::string link;
        std::cin >> link;
        if (link == "exit") {
            break;
        }
        std::ifstream file;
        file.open(link);

        Processor processor;

        processor.StartProgram(file);
        
    }
    
    return 0;
}
