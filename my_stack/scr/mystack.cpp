#include "mystack.h"

namespace StackLib {

    void * safe_calloc(std::size_t num, std::size_t size) {
        return calloc(num, size);
    }

    void * safe_realloc(int * ptr, std::size_t num, std::size_t size) {
        return realloc(ptr, num * size);
    }

    Stack::Stack() {
        std::cout << "Constructor\n";
        size_ = 0;
        capacity_ = 1;
        stack_ = (int *)safe_calloc(1, sizeof(int));
    }
    Stack::~Stack() {
        std::cout << "Destructor\n";
        delete[] stack_;
    }

    Stack::Stack(const Stack& other) {
        std::cout << "CopyConstructor\n";
        size_ = other.size_;
        capacity_ = other.capacity_;
        stack_ = (int*)safe_calloc(1, sizeof(int));
        memcpy(stack_, other.stack_, sizeof(int) * capacity_);        
    }
    Stack::Stack(const Stack&& other) {
        std::cout << "MoveConstructor\n";
        size_ = std::move(other.size_);
        capacity_ = std::move(other.capacity_);
        std::move(other.stack_, other.stack_ + other.capacity_, stack_); 
    }

    Stack& Stack::operator=(const Stack& other) {
        std::cout << "Copy=\n";
        size_ = other.size_;
        capacity_ = other.capacity_;
        stack_ = (int*)safe_calloc(1, sizeof(int));
        memcpy(stack_, other.stack_, sizeof(int) * capacity_);
        return *this;
    }
    Stack& Stack::operator=(Stack&& other) {
        std::cout << "Move=\n";
        size_ = std::move(other.size_);
        capacity_ = std::move(other.capacity_);
        std::move(other.stack_, other.stack_ + other.capacity_, stack_); 
        return *this;
    }

    void Stack::Pop() {
        if (size_ == 0) {
            return;
        }
        size_ -= 1;
        return;
    }
    void Stack::Push(int num) {
        if (size_ == capacity_) {
            capacity_ *= 2;
            stack_ = (int *)safe_realloc(stack_, capacity_, sizeof(int));
        }
        stack_[size_] = num;
        size_ += 1;
    }
    int Stack::Top() {
        if (size_ == 0) {
            return -1;
        }
        return stack_[size_ - 1];
    }

}