#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <exception>
#include "command.h"
#include "exception.h"

enum class TokenType {
    BEGIN,
    END,
    PUSH,
    POP,
    PUSHR,
    POPR,
    ADD,
    SUB,
    MUL,
    DIV,
    OUT,
    IN,
    JUMP,
    INIT,
    CALL,
    RET,
    LABEL,
    WORDINIT,
    UNDEFINED,
    INTEGER_VALUE,
    WORD,
};


struct Token {
    std::string value_;
    TokenType type_;
    Token(std::string value, TokenType type): value_(value), type_(type) {}
};


class Parser {

    public:

        std::vector<Token> FileParser(std::ifstream & file) {

            std::vector<Token> result;

            if (!file.is_open()) {
                throw ParserException{"File is not open"};
            }

            std::string cur_str;
            std::vector<std::string> str;
            while (file >> cur_str) {
                str.push_back(cur_str);
            }

            for (int i = 0 ; i < str.size(); i++) {
                for (int j = 0; j < tokens.size(); j++) {
                    if (std::regex_match(str[i], token_regex_[tokens[j]])) {
                        if (tokens[j] == TokenType::UNDEFINED) {
                            throw ParserException{"TokenType::UNDEFINED : " + str[i]};
                        }
                        Token new_token(str[i], tokens[j]);
                        result.push_back(new_token);
                        break;
                    } 
                }
            }

            return result;

        }

        int BuildVectorCommand(std::vector<Token>& vec_tokens, std::vector<std::shared_ptr<Command>> & vec_command,
                                AllMemory & all) {
            int begin = -1;
            std::string temp_label;
            for (int i = 0; i < vec_tokens.size(); i++) {
                switch(vec_tokens[i].type_) {
                    case TokenType::BEGIN:
                        if (begin != -1) {
                            throw ParserException{"Program starts twice."};
                        }
                        begin = vec_command.size();
                        vec_command.push_back(std::shared_ptr<Command> (new Begin()));
                        break;
                    
                    case TokenType::END:
                        vec_command.push_back(std::shared_ptr<Command> (new End()));
                        break;

                    case TokenType::PUSH:
                        if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::INTEGER_VALUE) {
                            throw ParserException{"Push command need value"};
                        }
                        i += 1;
                        vec_command.push_back(std::shared_ptr<Command> (new Push(stoi(vec_tokens[i].value_))));
                        break;

                    case TokenType::POP:
                        vec_command.push_back(std::shared_ptr<Command> (new Pop()));
                        break;
                    case TokenType::PUSHR:
                        if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                            throw ParserException{"PushR command need register"};
                        }
                        i += 1;
                        all.AddReg(vec_tokens[i].value_);

                        vec_command.push_back(std::shared_ptr<Command> (new PushR(vec_tokens[i].value_)));
                        break;

                    case TokenType::POPR:
                        if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                            throw ParserException{"PopR command need register"};
                        }
                        i += 1;
                        all.AddReg(vec_tokens[i].value_);
                        vec_command.push_back(std::shared_ptr<Command> (new PopR(vec_tokens[i].value_)));
                        break;
                    case TokenType::ADD:
                        vec_command.push_back(std::shared_ptr<Command> (new Add()));
                        break;
                    case TokenType::SUB:
                        vec_command.push_back(std::shared_ptr<Command> (new Sub()));
                        break;
                    case TokenType::MUL:
                        vec_command.push_back(std::shared_ptr<Command> (new Mul()));
                        break;
                    case TokenType::DIV:
                        vec_command.push_back(std::shared_ptr<Command> (new Div()));
                        break;
                    case TokenType::OUT:
                        vec_command.push_back(std::shared_ptr<Command> (new Out()));
                        break;
                    case TokenType::IN:
                        vec_command.push_back(std::shared_ptr<Command> (new In()));
                        break;
                    case TokenType::JUMP:
                        if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                            throw ParserException{vec_tokens[i].value_ + " command need a label"};
                        }
                        
                        vec_command.push_back(std::shared_ptr<Command> (new Jump(vec_tokens[i].value_, vec_tokens[i + 1].value_)));
                        i += 1;
                        break;
                    case TokenType::CALL:
                        if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                            throw ParserException{vec_tokens[i].value_ + " command need a label"};
                        }
                        vec_command.push_back(std::shared_ptr<Command> (new Call(vec_tokens[i + 1].value_)));
                        i += 1;
                        break;
                    case TokenType::RET:
                        vec_command.push_back(std::shared_ptr<Command> (new Ret()));
                        break;
                    case TokenType::WORD:
                        if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::INIT) {
                            throw ParserException{"Only word " + vec_tokens[i].value_};
                        }
                        if (i + 2 > vec_tokens.size() || vec_tokens[i + 2].type_ == TokenType::WORD) {
                            throw ParserException{"Function " + vec_tokens[i].value_ + " doesn't have any defenition"};
                        }
                        all.PushLable(vec_tokens[i].value_, vec_command.size());
                        
                        i += 1;
                        break;
                    case TokenType::WORDINIT:
                        if (i + 2 > vec_tokens.size() || vec_tokens[i + 1].type_ == TokenType::WORD ||
                            vec_tokens[i + 1].type_ == TokenType::WORDINIT) {
                            throw ParserException{"Function " + vec_tokens[i].value_ + " doesn't have any defenition"};
                        }
                        std::cout << vec_tokens[i].value_ << "!!!!   ";
                        temp_label = vec_tokens[i].value_;
                        temp_label.pop_back();
                        std::cout << temp_label << "\n";
                        all.PushLable(temp_label, vec_command.size());
                        break;
                    default:
                        throw ParserException{"Error in code of program : " +  vec_tokens[i].value_};
            
                }
                
            }
            return begin;
        }


    private:

        std::map<TokenType, std::regex> token_regex_ = {
                
                    {TokenType::BEGIN,     std::regex("BEGIN")},
                    {TokenType::END,     std::regex("END")},
                    {TokenType::PUSH,     std::regex("PUSH")},
                    {TokenType::POP,     std::regex("POP")},
                    {TokenType::PUSHR,     std::regex("PUSHR")},
                    {TokenType::POPR,     std::regex("POPR")},
                    {TokenType::ADD,     std::regex("ADD")},
                    {TokenType::SUB,     std::regex("SUB")},
                    {TokenType::MUL,     std::regex("MUL")},
                    {TokenType::DIV,     std::regex("DIV")},
                    {TokenType::OUT,     std::regex("OUT")},
                    {TokenType::IN,     std::regex("IN")},
                    {TokenType::JUMP,     std::regex("JMP|JEQ|JNE|JAE|JBE|JA|JB")},
                    {TokenType::CALL,     std::regex("CALL")},
                    {TokenType::RET,     std::regex("RET")},
                    {TokenType::INIT,     std::regex(":")},
                    {TokenType::WORDINIT,     std::regex("[a-zA-Z_][a-zA-Z0-9_]*:")},
                    {TokenType::UNDEFINED,     std::regex(".*")},
                    {TokenType::INTEGER_VALUE, std::regex("[-+]?[0-9]+")},
                    {TokenType::WORD,  std::regex("[a-zA-Z_][a-zA-Z0-9_]*")},

            };
        std::vector<TokenType> tokens = {TokenType::BEGIN,
                                        TokenType::END,
                                        TokenType::PUSH,
                                        TokenType::POP,
                                        TokenType::PUSHR,
                                        TokenType::POPR,
                                        TokenType::ADD,
                                        TokenType::SUB,
                                        TokenType::MUL,
                                        TokenType::DIV,
                                        TokenType::OUT,
                                        TokenType::IN,
                                        TokenType::JUMP,  
                                        TokenType::CALL,    
                                        TokenType::RET,
                                        TokenType::WORDINIT,     
                                        TokenType::INIT,
                                        TokenType::INTEGER_VALUE,
                                        TokenType::WORD,
                                        TokenType::UNDEFINED};


};
