#ifndef MY_STACK
#define MY_STACK
#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <exception>


namespace StackLib {

    class MyStackException: public std::exception {
        public:
            MyStackException(std::string message) : message_(message){}
            const char * what() const noexcept override;
        private:
            std::string message_;
    };


    template <typename T>
    class Stack {
        public:

            Stack() {
                size_ = 0;
                capacity_ = 1;
                stack_ = new T[capacity_];
            }

            ~Stack() {
                delete[] stack_;                
            }

            Stack(const Stack<T>& other) {
                size_ = other.size_;
                capacity_ = other.capacity_;
                stack_ = new T[capacity_];
                memcpy(stack_, other.stack_, sizeof(T) * capacity_);        
            }

            Stack(Stack<T>&& other) {
                swap(*this, other);
                other.stack_ = nullptr;
            }

            Stack<T>& operator=(const Stack<T>& other) {
                size_ = other.size_;
                capacity_ = other.capacity_;
                stack_ = new T[capacity_];
                memcpy(stack_, other.stack_, sizeof(T) * capacity_);
                return *this;
            }
            
            Stack<T>& operator=(Stack<T>&& other) {
                swap(*this, other);
                other.stack_ = nullptr;
                return *this;
            }

            void Pop() {
                if (size_ == 0) {
                    throw MyStackException{"Stack is empty"};
                }
                size_ -= 1;
                return;
            }

            void Push(auto num) {
                if (size_ == capacity_) {
                    T * new_stack = new T[capacity_ * 2];
                    memcpy(new_stack, stack_, sizeof(T) * capacity_);
                    std::swap(new_stack, stack_);
                    capacity_ *= 2;
                    delete[] new_stack;
                }
                stack_[size_] = num;
                size_ += 1;
            }

            T Top() {
                if (size_ == 0) {
                    throw MyStackException{"Stack is empty"};
                }
                return stack_[size_ - 1];
            }

            int Size() {
                return size_;
            }

            const T& Top() const {
                if (size_ == 0) {
                    throw MyStackException{"Stack is empty"};
                }
                return stack_[size_ - 1];
            }
        
            bool IsEmpty() {
                return (int)size_ == 0;
            }

        private:
            int size_;
            int capacity_;
            T * stack_;

            friend void swap(Stack & first, Stack & second) {
                std::swap(first.size_, second.size_);
                std::swap(first.capacity_, second.capacity_);
                std::swap(first.stack_, second.stack_);
            }
    };
}
#endif
