#ifndef EXCEPTION
#define EXCEPTION
#include <exception>


class CommandException: public std::exception {
    public:
        CommandException(std::string message) : message_(message.c_str()){}
        const char * what() const noexcept override {
            return message_;
        }
    private:
        const char * message_;
};

class ParserException: public std::exception {
    public:
        ParserException(std::string message) : message_(message.c_str()){}
        const char * what() const noexcept override {
            return message_;
        }
    private:
        const char * message_;
};


class ProcessorException: public std::exception {
    public:
        ProcessorException(std::string message) : message_(message.c_str()){}
        const char * what() const noexcept override {
            return message_;
        }
    private:
        const char * message_;
};

#endif
