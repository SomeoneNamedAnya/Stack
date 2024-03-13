#ifndef COMMAND
#define COMMAND
#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <exception>
#include <string>
#include "mystack.h"


namespace CommandLib{

    class Element {
        public:
            int value_;
            int * reg_ = nullptr;
            bool is_reg_;
            Element():reg_(nullptr) {}
            Element(int value, bool is_reg): value_(value), is_reg_(is_reg), reg_(nullptr) {}
            Element(int value, bool is_reg, int * reg): value_(value), is_reg_(is_reg), reg_(reg) {}

            friend Element operator+(const Element& first, const Element& second) {
                Element ans(first.GetNum() + second.GetNum(), false);
                return ans;
            }

            friend Element operator-(const Element& first, const Element& second) {
                Element ans(first.GetNum() - second.GetNum(), false);
                return ans;
            }

            friend Element operator*(const Element& first, const Element& second) {
                Element ans(first.GetNum() * second.GetNum(), false);
                return ans;
            }

            friend Element operator/(const Element& first, const Element& second) {
                Element ans(first.GetNum() / second.GetNum(), false);
                return ans;
            }

            int GetNum() const {
                if (is_reg_) {
                    return *reg_;
                } else {
                    return value_;
                }
            }
    };
    
    class Command {
        public:
            virtual void execute(StackLib::Stack<Element> * &) = 0;
            virtual std::string name() = 0;
    };

    class Begin: public Command {
        public:
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack != nullptr) {
                    throw "process has already been started ";
                }
                stack = new StackLib::Stack<Element>;
            }
            virtual std::string name() override {
                return "BEGIN";
            }
    };

    class End: public Command {
        public:
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process has already been finished ";
                }
                delete stack;
            }
            virtual std::string name() override {
                return "END";
            }

    };

    class Push: public Command {
        public:
            Push(int value):value_(value) {}
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                stack -> Push(Element(value_, false));
                
            }
            virtual std::string name() override {
                return "PUSH";
            }
        private:
            int value_;

    };

    class Pop: public Command {
        public:

            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                stack -> Pop();
                
            }
            virtual std::string name() override {
                return "POP";
            }

    };

    class PushR: public Command {
        public:
            PushR(int * value):value_(value) {}
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                
                stack -> Push(Element(*value_, true, value_));
                
            }
            virtual std::string name() override {
                return "PUSHR";
            }
        private:
            int * value_;

    };

    class PopR: public Command {
        public:
            PopR(int * value):value_(value) {}
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                *value_ = (stack -> Top()).GetNum();
                stack -> Pop();
            }
            virtual std::string name() override {
                return "POPR";
            }
        private:
            int * value_;

    };

    class Add: public Command {
        public:
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                Element first = stack -> Top();
                stack -> Pop();
                Element second = stack -> Top();
                stack -> Pop();
                stack -> Push(second);
                stack -> Push(first);
                stack -> Push(first + second);
            }
            virtual std::string name() override {
                return "ADD";
            }
    };

    class Sub: public Command {
        public:
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                Element first = stack -> Top();
                stack -> Pop();
                Element second = stack -> Top();
                stack -> Pop();
                stack -> Push(second);
                stack -> Push(first);
                stack -> Push(first - second);
            }
            virtual std::string name() override {
                return "SUB";
            }
    };

    class Mul: public Command {
        public:
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                Element first = stack -> Top();
                stack -> Pop();
                Element second = stack -> Top();
                stack -> Pop();
                stack -> Push(second);
                stack -> Push(first);
                stack -> Push(first * second);
            }
            virtual std::string name() override {
                return "MUL";
            }
    };

    class Div: public Command {
        public:
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                Element first = stack -> Top();
                stack -> Pop();
                Element second = stack -> Top();
                stack -> Pop();
                stack -> Push(second);
                stack -> Push(first);
                stack -> Push(first / second);
            }
            virtual std::string name() override {
                return "DIV";
            }
    };

    class Out: public Command {
        public:
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                Element first = stack -> Top();
                stack -> Pop();
                std::cout << first.GetNum() << "\n";
            }
            virtual std::string name() override {
                return "OUT";
            }
    };

    class In: public Command {
        public:
            void execute(StackLib::Stack<Element> * & stack) override {
                if (stack == nullptr) {
                    throw "process is not started";
                }
                int value;
                std::cin >> value;
                Element first(value, false);
                stack -> Push(first);
            }
            virtual std::string name() override {
                return "IN";
            }
    };
}
#endif