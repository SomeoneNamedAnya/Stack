#ifndef COMMAND
#define COMMAND
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <exception>
#include <string>
#include "mystack.h"


class CommandExeption {
    public:
        CommandExeption(const std::string& message) : message_(message){}
        virtual std::string what() {
            return message_;
        }
    private:
        std::string message_;
};

class Command;

class AllMemory {
    public:
        bool start_ = false;
        std::vector<StackLib::Stack<int>> stack_;
        std::map<std::string, int> reg_;
        std::map<std::string, int> func_;
        std::vector<int> cur_pos_;

        void SetPos(int pos) {
            cur_pos_.push_back(pos);
        }

        bool IsStart() {
            return start_;
        }

        void Start() {
            start_ = true;
            stack_.push_back(StackLib::Stack<int>());
        }

        void End() {
            start_ = false;
            stack_.clear();
        }

        void Push(int value) {
            stack_[stack_.size() - 1].Push(value);
        }

        void Pop() {
            stack_[stack_.size() - 1].Pop();
        }

        int Top() {
            return stack_[stack_.size() - 1].Top();
        }

        void WriteReg(std::string reg, int value) {
            reg_[reg] = value;
        }

        int GetReg(std::string reg) {
            return reg_[reg];
        }

        void PushLable(std::string label, int pos) {
            if (func_.find(label) != func_.end()) {
                throw CommandExeption{"The function " + label + " is already determined."};
            }
            func_[label] = pos;
        }

        void Goto(std::string label) {
            cur_pos_.back() = func_[label] - 1;
        }

        void Call(std::string label) {
            cur_pos_.push_back(func_[label] - 1);
            stack_.push_back(stack_.back());
        }

        void Ret() {
            cur_pos_.pop_back();
            stack_.pop_back();
        }

        bool CanStep(int size) {
            return cur_pos_.back() < size;
        }
};
class Command {
    public:
        virtual void execute(AllMemory & all) = 0;
        virtual std::string name() = 0;
        
};


void Step(std::vector<Command * > & vec_command, AllMemory & all) {
    vec_command[all.cur_pos_.back()] -> execute(all);
    all.cur_pos_[all.cur_pos_.size() - 1] += 1;
}

class Begin: public Command {
    public:
        void execute(AllMemory & all) override {
            if (all.IsStart()) {
                throw CommandExeption{"The process has already been started"};
            }
            all.Start();
        }
        std::string name() override {
            return "BEGIN";
        }
};

class End: public Command {
    public:
        void execute(AllMemory & all) override {
            if (!all.IsStart()) {
                throw CommandExeption{"The process has already been finished"};
            }
           all.End();
        }
        std::string name() override {
            return "END";
        }
};

class Push: public Command {
    public:
        Push(int value):value_(value) {}
        void execute(AllMemory & all) override {
            if (!all.IsStart()) {
                throw CommandExeption{"The process is not started"};
            }
            all.Push(value_);
            
        }
        std::string name() override {
            return "PUSH";
        }
    private:
        int value_;
};

class Pop: public Command {
    public:
        void execute(AllMemory & all) override {
            if (!all.IsStart()) {
                throw CommandExeption{"The process is not started"};
            }
            all.Pop();
            
        }
        std::string name() override {
            return "POP";
        }
};

class PushR: public Command {
    public:
        PushR(std::string & reg): reg_(reg) {}
        void execute(AllMemory & all) override {
            if (!all.IsStart()) { 
                throw CommandExeption{"The process is not started"};
            }
            
            all.Push(all.GetReg(reg_));
            
        }
        std::string name() override {
            return "PUSHR";
        }
    private:
        std::string reg_;
};

class PopR: public Command {
    public:
        PopR(std::string reg): reg_(reg) {}
        void execute(AllMemory & all) override {
            if (!all.IsStart()) { 
                throw CommandExeption{"The process is not started"};
            }
            all.WriteReg(reg_, all.Top());
            all.Pop();
        }
        std::string name() {
            return "POPR";
        }
    private:
        std::string reg_;

};

class Add: public Command {
    public:
        void execute(AllMemory & all) override {
            if (!all.IsStart()) { 
                throw CommandExeption{"The process is not started"};
            }
            int first = all.Top();
            all.Pop();
            int second = all.Top();
            all.Pop();
            all.Push(first + second);
        }
        
        std::string name() override {
            return "ADD";
        }
};

class Sub: public Command {
    public:
        void execute(AllMemory & all) override {
            if (!all.IsStart()) {
                throw CommandExeption{"The process is not started"};
            }
            int first = all.Top();
            all.Pop();
            int second = all.Top();
            all.Pop();
            all.Push(first - second);
        }
        
        std::string name() override {
            return "SUB";
        }
};

class Mul: public Command {
    public:
        void execute(AllMemory & all) override {
            if (!all.IsStart()) { 
                throw CommandExeption{"The process is not started"};
            }
            int first = all.Top();
            all.Pop();
            int second = all.Top();
            all.Pop();
            all.Push(first * second);
        }
        
        std::string name() override {
            return "MUL";
        }
};

class Div: public Command {
    public:
        void execute(AllMemory & all) override {
            if (!all.IsStart()) { 
                throw CommandExeption{"The process is not started"};
            }
            int first = all.Top();
            all.Pop();
            int second = all.Top();
            all.Pop();
            all.Push(first / second);
        }
        
        std::string name() override {
            return "DIV";
        }
};

class Out: public Command {
    public:
        void execute(AllMemory & all) override {
            if (!all.IsStart()) {
                throw CommandExeption{"The process is not started"};
            }
            int first = all.Top();
            all.Pop();
            std::cout << first << "\n";
        }
        std::string name() override {
            return "OUT";
        }
};

class In: public Command {
    public:
        void execute(AllMemory & all) override {
            if (!all.IsStart()) {
                throw CommandExeption{"The process is not started"};
            }
            int value;
            std::cin >> value;
            all.Push(value);
        }
        std::string name() override {
            return "IN";
        } 
};

class Jump: public Command {
    public:
        Jump(std::string type, std::string label): type_(type), label_(label) {}
        void execute(AllMemory & all) override {
            if (!all.IsStart()) {
                throw CommandExeption{"The process is not started"};
            }

            if (type_ == "JMP") {
                all.Goto(label_);
            } else if (type_ == "JEQ") {
                int first = all.Top();
                all.Pop();
                int second = all.Top();
                all.Pop();
                if (first == second) {
                    all.Goto(label_);
                }
            } else if (type_ == "JNE") {
                int first = all.Top();
                all.Pop();
                int second = all.Top();
                all.Pop();
                if (first != second) {
                    all.Goto(label_);
                }
            } else if (type_ == "JA") {
                int first = all.Top();
                all.Pop();
                int second = all.Top();
                all.Pop();
                if (first > second) {
                    all.Goto(label_);
                }
            } else if (type_ == "JAE") {
                int first = all.Top();
                all.Pop();
                int second = all.Top();
                all.Pop();
                if (first >= second) {
                    all.Goto(label_);
                }
            } else if (type_ == "JB") {
                
                int first = all.Top();
                all.Pop();
                int second = all.Top();
                all.Pop();
               // std::cout << first << " " << second << "###########\n";
                if (first < second) {
                //    std::cout << "############\n";
                    all.Goto(label_);
                }
            } else if (type_ == "JBE") {
                int first = all.Top();
                all.Pop();
                int second = all.Top();
                all.Pop();
                if (first <= second) {
                    all.Goto(label_);
                }
            }

        }
        std::string name() override {
            return type_;
        } 
    private:
        std::string type_;
        std::string label_;
};

class Call: public Command {
    public:
        Call(std::string & label): label_(label) {}
        void execute(AllMemory & all) override {
            if (!all.IsStart()) { 
                throw CommandExeption{"The process is not started"};
            }
            
            all.Call(label_);
            
        }
        std::string name() override {
            return "CALL";
        }
    private:
        std::string label_;
};

class Ret: public Command {
    public:
        void execute(AllMemory & all) override {
            if (!all.IsStart()) { 
                throw CommandExeption{"The process is not started"};
            }
            
            all.Ret();
            
        }
        std::string name() override {
            return "RET";
        }
};

#endif