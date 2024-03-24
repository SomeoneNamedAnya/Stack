#include "mystack.h"

using namespace StackLib; 

const char * MyStackException::what() const noexcept {
    return message_.c_str();
}
