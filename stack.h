/*
 * File: stack.h
 * Author: Aniketh Sriramoju
 * Date: June 21, 2026
 * Description: Interface for the Stack ADT. Implements a fixed-size
 *              integer stack backed by a static array. Provides push,
 *              pop, peek, and isEmpty operations. Underflow conditions
 *              on pop() and peek() are reported via exception handling
 *              (std::underflow_error) rather than a special return value.
 */

#ifndef STACK_H
#define STACK_H

#include <stdexcept>

// Maximum capacity of the stack. Declared here (not inside the class
// or the .cpp file) so client code, such as main.cpp, can see it and
// build tests that automatically scale if this value is changed.
const int STACK_SIZE = 10;

// Sentinel value for "top" when the stack holds no elements.
const int EMPTY_TOP = -1;

class Stack {
private:
    int data[STACK_SIZE];
    int top;

public:
    /*
     * Function: Stack (constructor)
     * Description: Initializes an empty stack.
     * Parameters: none
     * Return: none
     */
    Stack();

    /*
     * Function: push
     * Description: Inserts a value onto the top of the stack.
     * Parameters: value - the integer value to push
     * Return: bool - true if the push succeeded, false if the stack
     *         was already full (overflow)
     */
    bool push(int value);

    /*
     * Function: pop
     * Description: Removes and returns the value at the top of the stack.
     * Parameters: none
     * Return: int - the value removed from the top of the stack
     * Throws: std::underflow_error if the stack is empty
     */
    int pop();

    /*
     * Function: peek
     * Description: Returns the value at the top of the stack without
     *              removing it.
     * Parameters: none
     * Return: int - the value currently at the top of the stack
     * Throws: std::underflow_error if the stack is empty
     */
    int peek();

    /*
     * Function: isEmpty
     * Description: Tests whether the stack currently holds no elements.
     * Parameters: none
     * Return: bool - true if the stack is empty (top < 0), false otherwise
     */
    bool isEmpty();
};

#endif
