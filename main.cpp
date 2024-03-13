#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>
#include "mystack.h"
#include "parser.h"
#include "command.h"
using namespace StackLib;


int main(){
    
    std::cout << "put link:\n";
    std::string link = "code_1.txt";
    //std::cin >> link;
    std::ifstream file;
    file.open(link);
    std::vector<Token> tokens = file_parser(file);
    std::cout << "put link:\n";
    Stack<CommandLib::Element> * stack = nullptr;
    std::map<std::string, int> map_reg;
    std::vector<CommandLib::Command *> vec_command;

    build_vector_command(tokens, vec_command, map_reg);
    try{
        for (int i = 0; i < vec_command.size(); i++) {
            //std::cout << i << std::endl;
            vec_command[i] -> execute(stack);
        }
    } catch (char const* error) {
        std::cout << error;
    }


    
    return 0;
}
