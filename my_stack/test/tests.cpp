#include <gtest/gtest.h>
#include <exception>
#include <string>

#include "mystack.h"
using namespace StackLib;

TEST(Push, PushIn) {
    Stack<int> first;

    EXPECT_NO_THROW(first.Push(123)) << "Исключение";
    EXPECT_NO_THROW(first.Push(23)) << "Исключение";
    EXPECT_NO_THROW(first.Push(12300)) << "Исключение";
    EXPECT_NO_THROW(first.Push(123000)) << "Исключение"; 

    for (int i = 0; i < 100; i++) {
        EXPECT_NO_THROW(first.Push(123000)) << "Исключение"; 
    }

}

TEST(Pop, PopOut) {
    Stack<int> first;

    for (int i = 0; i < 100; i++) {
        first.Push(123000); 
    }

    for (int i = 0; i < 100; i++) {
        EXPECT_NO_THROW(first.Pop()) << "Исключение"; 
    }
    ASSERT_ANY_THROW(first.Pop()) << "Нет исключения";
}


TEST(Top, PushIn) {
  Stack<int> first;

  EXPECT_ANY_THROW(first.Top()) << "Нет исключения";
  
  first.Push(123);
  EXPECT_EQ(first.Top(), 123) << first.Top() << " " << 123;

  first.Push(-321);
  EXPECT_EQ(first.Top(), -321) << first.Top() << " " << -321;

  first.Push(5555);
  EXPECT_EQ(first.Top(), 5555) << first.Top() << " " << 5555;
  
}

TEST(IsEmpty, IsEmpty) {
  Stack<int> first;

  EXPECT_EQ(first.IsEmpty(), true) << first.IsEmpty() << " " << true;

  first.Push(123);
  EXPECT_EQ(first.IsEmpty(), false) << first.IsEmpty() << " " << true;

  first.Pop();
  EXPECT_EQ(first.IsEmpty(), true) << first.IsEmpty() << " " << true;

}
