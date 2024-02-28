#include "Stack.h"

using namespace StackLib;

    void * safe_calloc(size_t num, size_t size) {
        return calloc(num, size);
    }

    void * safe_realloc(int * ptr, size_t num, size_t size) {
        return realloc(ptr, num * size);
    }

    Stack::Stack() {
        size_ = 0;
        capacity_ = 1;
        stack_ = (int *)safe_calloc(1, sizeof(int));
    }
    Stack::~Stack() {
        delete[] stack_;
    }

    Stack::Stack(const Stack& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        stack_ = (int*)safe_calloc(1, sizeof(int));
        memcpy(stack_, other.stack_, sizeof(int) * capacity_);        
    }
    Stack::Stack(const Stack&& other) {
        size_ = std::move(other.size_);
        capacity_ = std::move(other.capacity_);
        std::move(other.stack_, other.stack_ + other.capacity_, stack_); 
    }

        //Stack& operator=(const Stack& other);
        //Stack& operator=(Stack&& other);

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

