#ifndef EXCEPTION
#define EXCEPTION
#include <exception>


class CommandException: public std::exception {
    public:
        CommandException(std::string message) : message_(message){}
        const char * what() const noexcept override {
            return message_.c_str();
        }
    private:
        std::string message_;
};

class ParserException: public std::exception {
    public:
        ParserException(std::string message) : message_(message){}
        const char * what() const noexcept override {
            return message_.c_str();
        }
    private:
        std::string message_;
};



class ProcessorException: public std::exception {
    public:
        ProcessorException(std::string message) : message_(message){}
        const char * what() const noexcept override {
            return message_.c_str();
        }
    private:
        std::string message_;
};
#endif
