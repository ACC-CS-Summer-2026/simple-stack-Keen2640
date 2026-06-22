/*
 * File: stack.cpp
 * Author: Aniketh Sriramoju
 * Date: June 21, 2026
 * Description: Implementation of the Stack ADT declared in stack.h.
 */

#include "stack.h"

/*
 * Function: Stack (constructor)
 * Description: Initializes an empty stack by setting top to EMPTY_TOP.
 * Parameters: none
 * Return: none
 */
Stack::Stack() {
    top = EMPTY_TOP;
}

/*
 * Function: push
 * Description: Inserts a value onto the top of the stack if room remains.
 * Parameters: value - the integer value to push
 * Return: bool - true if the value was pushed, false if the stack
 *         was full (overflow), in which case no state is changed
 */
bool Stack::push(int value) {
    bool success;

    if (top >= STACK_SIZE - 1) {
        success = false;
    } else {
        top++;
        data[top] = value;
        success = true;
    }

    return success;
}

/*
 * Function: pop
 * Description: Removes and returns the value at the top of the stack.
 * Parameters: none
 * Return: int - the value removed from the top of the stack
 * Throws: std::underflow_error if the stack is empty
 */
int Stack::pop() {
    int value;

    if (isEmpty()) {
        throw std::underflow_error("Stack underflow: cannot pop an empty stack.");
    }

    value = data[top];
    top--;

    return value;
}

/*
 * Function: peek
 * Description: Returns the value at the top of the stack without
 *              removing it.
 * Parameters: none
 * Return: int - the value currently at the top of the stack
 * Throws: std::underflow_error if the stack is empty
 */
int Stack::peek() {
    int value;

    if (isEmpty()) {
        throw std::underflow_error("Stack underflow: cannot peek an empty stack.");
    }

    value = data[top];

    return value;
}

/*
 * Function: isEmpty
 * Description: Tests whether the stack is empty.
 * Parameters: none
 * Return: bool - true if top is less than 0, false otherwise
 */
bool Stack::isEmpty() {
    return (top <= EMPTY_TOP);
}
