#include <iostream>
#include <string>
#include "mystack.h"
using namespace StackLib;

/*void f(Stack<int> q) {
    return;
}*/
int main(){
    /*Stack <int> my_stack;
    my_stack.Push(1);
    my_stack.Push(2);

    std::cout << my_stack.Top() << "\n";
    my_stack.Pop();
    std::cout << my_stack.Top() << "\n";
    my_stack.Pop();
    my_stack.Push(3);
    std::cout << my_stack.Top() << "\n";
    
    Stack<int> second, third;
    second = my_stack;
    third = std::move(my_stack);
    std::cout << second.Top() << "\n";

    std::cout << third.Top() << "\n";
   // f(second);
    std::cout << second.Top() << "\n";*/
    Stack<std::string> str_stack;
    str_stack.Push("qwe");
    str_stack.Push("aaa");
    str_stack.Push("qqq");

    while (!str_stack.IsEmpty()) {
        std::cout << str_stack.Top() << "\n";
        str_stack.Pop();
    }
    str_stack.Pop();
    return 0;
}
