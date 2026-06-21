/*****************************************************************
 * File: stack.h
 * Author: Aniketh Sriramoju
 * Date: June 21, 2026
 * Description: Interface for a fixed-size integer Stack ADT.
 *              Provides push, pop, peek, and isEmpty operations.
 *              Underflow on pop()/peek() is reported via the
 *              StackException class. Overflow on push() is
 *              reported via a boolean return value.
 *****************************************************************/

#ifndef STACK_H
#define STACK_H

#include <exception>
#include <string>

// Maximum capacity of the stack. Change this one value to resize
// the stack for testing; all dependent code (including main's
// tests) scales automatically since it is referenced, not hardcoded.
const int STACK_SIZE = 10;

/*****************************************************************
 * Class: StackException
 * Description: Exception thrown by Stack::pop() and Stack::peek()
 *              when invoked on an empty stack (underflow).
 *****************************************************************/
class StackException : public std::exception {
private:
    std::string message;

public:
    explicit StackException(const std::string &msg);
    const char* what() const noexcept override;
};

/*****************************************************************
 * Class: Stack
 * Description: A simple fixed-capacity LIFO integer stack backed
 *              by a statically-sized array of STACK_SIZE elements.
 *****************************************************************/
class Stack {
private:
    int stackArray[STACK_SIZE];
    int top;

public:
    Stack();

    int pop();             // remove and return top value; throws StackException if empty
    int peek() const;      // return top value without removing; throws StackException if empty
    bool push(int value);  // insert value at top; returns false on overflow
    bool isEmpty() const;  // returns true if top < 0
};

#endif
