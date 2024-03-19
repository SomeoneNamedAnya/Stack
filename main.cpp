#include <iostream>
#include "parser.h"

int main(){
    
    std::cout << "put link:\n";
    std::string link;
    std::cin >> link;
    std::ifstream file;
    file.open(link);
try{
        std::vector<Token> tokens = file_parser(file);
        AllMemory all;
        std::vector<Command *> vec_command;
        int begin = build_vector_command(tokens, vec_command, all);
        all.SetPos(begin);
    
        while (all.CanStep(vec_command.size())) {
            Step(vec_command, all);
        }
    }  catch (ParserExeption& error) {
        std::cout << error.what();
    } catch (StackLib::MyStackExeption& error) {
        std::cout << error.what();
    } catch (CommandExeption& error) {
        std::cout << error.what();
    }


    
    return 0;
}
