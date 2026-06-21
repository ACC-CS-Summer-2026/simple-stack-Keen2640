/*****************************************************************
 * File: stack.cpp
 * Author: Aniketh Sriramoju
 * Date: June 21, 2026
 * Description: Implementation of the Stack ADT and StackException
 *              class declared in stack.h.
 *****************************************************************/

#include "stack.h"

/*****************************************************************
 * Function: StackException::StackException
 * Description: Constructs an exception carrying an error message.
 * Parameters: msg - description of the error condition
 * Returns: none (constructor)
 *****************************************************************/
StackException::StackException(const std::string &msg) : message(msg) {
}

/*****************************************************************
 * Function: StackException::what
 * Description: Returns the error message for this exception.
 * Parameters: none
 * Returns: const char* - the error message
 *****************************************************************/
const char* StackException::what() const noexcept {
    return message.c_str();
}

/*****************************************************************
 * Function: Stack::Stack
 * Description: Constructs an empty stack.
 * Parameters: none
 * Returns: none (constructor)
 *****************************************************************/
Stack::Stack() : top(-1) {
}

/*****************************************************************
 * Function: Stack::isEmpty
 * Description: Tests whether the stack currently holds no values.
 * Parameters: none
 * Returns: bool - true if the stack is empty, false otherwise
 *****************************************************************/
bool Stack::isEmpty() const {
    return top < 0;
}

/*****************************************************************
 * Function: Stack::push
 * Description: Inserts a value onto the top of the stack.
 * Parameters: value - the integer to push
 * Returns: bool - true on success, false if the stack is full
 *****************************************************************/
bool Stack::push(int value) {
    bool success;

    if (top >= STACK_SIZE - 1) {
        success = false;
    } else {
        top++;
        stackArray[top] = value;
        success = true;
    }

    return success;
}

/*****************************************************************
 * Function: Stack::pop
 * Description: Removes and returns the value at the top of the
 *              stack.
 * Parameters: none
 * Returns: int - the value formerly at the top of the stack
 * Throws: StackException if the stack is empty
 *****************************************************************/
int Stack::pop() {
    int value;

    if (isEmpty()) {
        throw StackException("Stack underflow: cannot pop an empty stack.");
    }

    value = stackArray[top];
    top--;

    return value;
}

/*****************************************************************
 * Function: Stack::peek
 * Description: Returns the value at the top of the stack without
 *              removing it.
 * Parameters: none
 * Returns: int - the value at the top of the stack
 * Throws: StackException if the stack is empty
 *****************************************************************/
int Stack::peek() const {
    int value;

    if (isEmpty()) {
        throw StackException("Stack underflow: cannot peek an empty stack.");
    }

    value = stackArray[top];

    return value;
}
