#include "exception.h"
#include "parser.h"

class Processor {
    public:

        void Step(std::vector<std::shared_ptr<Command>> & vec_command, AllMemory & all) {
            vec_command[all.cur_pos_.back()] -> execute(all);
            all.cur_pos_[all.cur_pos_.size() - 1] += 1;
        }
        
        bool StartProgram(std::ifstream & file) {

            try{
                if (!file.is_open()) {
                    throw ProcessorException{"File isn't open."};
                }
                Parser parser;
                std::vector<Token> tokens = parser.FileParser(file);
                AllMemory all;
                std::vector<std::shared_ptr<Command>> vec_command;
                
                int begin = parser.BuildVectorCommand(tokens, vec_command, all);
                all.SetPos(begin);
            
                while (all.CanStep(vec_command.size())) {
                    Step(vec_command, all);
                }
                return true;

            }  catch (ParserException& error) {
                std::cout << error.what();
                return false;
            } catch (StackLib::MyStackException& error) {
                std::cout<< "MyStackException: " << error.what();
                return false;
            } catch (CommandException& error) {
                std::cout << "CommandException: " << error.what();
                return false;
            } catch (ProcessorException& error) {
                std:: cout << "ProcessorException: " << error.what();
                return false;
            }

        }


};
