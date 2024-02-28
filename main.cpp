#include <iostream>
#include "mystack.h"
using namespace StackLib;

void f(Stack q) {
    return;
}
int main(){
    Stack my_stack;
    my_stack.Push(1);
    my_stack.Push(2);

    /*std::cout << my_stack.Top() << "\n";
    my_stack.Pop();
    std::cout << my_stack.Top() << "\n";
    my_stack.Pop();
    my_stack.Push(3);
    std::cout << my_stack.Top() << "\n";
    */
    Stack second, third;
    second = my_stack;
    third = std::move(my_stack);
    std::cout << second.Top() << "\n";

    std::cout << third.Top() << "\n";
    f(second);
    std::cout << second.Top() << "\n";
    return 0;
}