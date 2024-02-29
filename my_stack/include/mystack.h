#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <exception>

namespace StackLib{
    template <typename T>
    class Stack {
        public:

            Stack() {
                size_ = 0;
                capacity_ = 1;
                stack_ = (T *)safe_calloc(1, sizeof(T));
            }

            ~Stack() {
                free(stack_);
            }

            Stack(const Stack<T>& other) {
                size_ = other.size_;
                capacity_ = other.capacity_;
                stack_ = (T*)safe_calloc(1, sizeof(T));
                memcpy(stack_, other.stack_, sizeof(T) * capacity_);        
            }

            Stack(const Stack<T>&& other) {
                size_ = std::move(other.size_);
                capacity_ = std::move(other.capacity_);
                std::move(other.stack_, other.stack_ + other.capacity_, stack_); 
            }

            Stack<T>& operator=(const Stack<T>& other) {
                size_ = other.size_;
                capacity_ = other.capacity_;
                stack_ = (T*)safe_calloc(1, sizeof(T));
                memcpy(stack_, other.stack_, sizeof(T) * capacity_);
                return *this;
            }
            
            Stack<T>& operator=(Stack<T>&& other) {
                size_ = std::move(other.size_);
                capacity_ = std::move(other.capacity_);
                std::move(other.stack_, other.stack_ + other.capacity_, stack_); 
                return *this;
            }

            void Pop() {
                if (size_ == 0) {
                    throw "Stack is empty";
                }
                size_ -= 1;
                return;
            }

            void Push(T num) {
                if (size_ == capacity_) {
                    capacity_ *= 2;
                    stack_ = (T *)safe_realloc(stack_, capacity_, sizeof(T));
                }
                stack_[size_] = num;
                size_ += 1;
            }

            T Top() {
                if (size_ == 0) {
                    throw "Stack is empty";
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

            void * safe_calloc(std::size_t num, std::size_t size) {
                return calloc(num, size);
            }

            void * safe_realloc(T * ptr, std::size_t num, std::size_t size) {
                return realloc(ptr, num * size);
            }
    };
}
