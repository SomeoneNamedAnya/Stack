#ifndef PARSER
#define PARSER
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <exception>
#include "command.h"

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
    UNDEFINED,
    INTEGER_VALUE,
    WORD,
};
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
                                 TokenType::INTEGER_VALUE,
                                 TokenType::WORD,
                                 TokenType::UNDEFINED};

struct Token {
    std::string value_;
    TokenType type_;
    Token(std::string value, TokenType type): value_(value), type_(type) {}
};

std::vector<Token> file_parser(std::ifstream & file) {

    std::vector<Token> result;

    if (!file.is_open()) {
        std::cout << "is not open\n";
        throw 7;
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
                    std::cout << str[i] << " UNDEFINED\n";
                    throw "TokenType::UNDEFINED";
                }
                Token new_token(str[i], tokens[j]);
                result.push_back(new_token);
                break;
            } 
        }
    }

    return result;

}

void build_vector_command(std::vector<Token>& vec_tokens, std::vector<CommandLib::Command*>& vec_command, 
                          std::map<std::string, int>& map_reg) {
    
    for (int i = 0 ; i < vec_tokens.size(); i++) {
        switch(vec_tokens[i].type_) {
            case TokenType::BEGIN:
                vec_command.push_back(new CommandLib::Begin());
                break;
            
            case TokenType::END:
                vec_command.push_back(new CommandLib::End());
                break;

            case TokenType::PUSH:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::INTEGER_VALUE) {
                    std::cout << "Push command need value\n";
                    throw "Push command need value";
                }
                i += 1;
                vec_command.push_back(new CommandLib::Push(stoi(vec_tokens[i].value_)));
                break;

            case TokenType::POP:
                vec_command.push_back(new CommandLib::Pop());
                break;
            case TokenType::PUSHR:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    std::cout << "PushR command need reg\n";
                    throw "PushR command need reg";
                }
                i += 1;
                if (map_reg.find(vec_tokens[i].value_) == map_reg.end()) {
                    map_reg[vec_tokens[i].value_] = 0;
                }

                vec_command.push_back(new CommandLib::PushR(&map_reg[vec_tokens[i].value_]));
                break;

            case TokenType::POPR:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    std::cout << "PopR command need reg\n";
                    throw "PophR command need reg";
                }
                i += 1;
                if (map_reg.find(vec_tokens[i].value_) == map_reg.end()) {
                    map_reg[vec_tokens[i].value_] = 0;
                }
                vec_command.push_back(new CommandLib::PopR(&map_reg[vec_tokens[i].value_]));
                break;
            case TokenType::ADD:
                vec_command.push_back(new CommandLib::Add());
                break;
            case TokenType::SUB:
                vec_command.push_back(new CommandLib::Sub());
                break;
            case TokenType::MUL:
                vec_command.push_back(new CommandLib::Mul());
                break;
            case TokenType::DIV:
                vec_command.push_back(new CommandLib::Div());
                break;
            case TokenType::OUT:
                vec_command.push_back(new CommandLib::Out());
                break;
            case TokenType::IN:
                vec_command.push_back(new CommandLib::In());
                break;
            default:
                std::cout << "error in code\n";
                throw "Error in code";
    
        }
    
    }

}
#endif
