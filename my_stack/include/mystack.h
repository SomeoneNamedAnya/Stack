#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <algorithm>
namespace StackLib{
    class Stack {
        public:
            Stack();
            ~Stack();

            Stack(const Stack&);
            Stack(const Stack&&);

            Stack& operator=(const Stack& other);
            Stack& operator=(Stack&& other);

            void Pop();
            void Push(int);
            int Top();

        private:
            int size_;
            int capacity_;
            int * stack_;
    };
}