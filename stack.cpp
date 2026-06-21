/* *************************************************
*  Name: Aniketh Sriramoju
*  Assignment: Assignment 4
*  Purpose: Class definition file for an integer Stack ADT
************************************************* */

#include "stack.h"
#include <stdexcept>

Stack::Stack()
{
/* **************************
* Default constructor, initializes top to -1 (empty)
*
* @param : none
* @exception : none
* @return : void
* @note : none
****************************/
    top = -1;
}

bool Stack::isEmpty()
{
/* **************************
* Tests whether the stack is empty
*
* @param : none
* @exception : none
* @return bool : true if empty, false otherwise
* @note : none
****************************/
    return top < 0;
}

bool Stack::push(int value)
{
/* **************************
* Pushes a value onto the top of the stack,
* if there is room. Returns false on overflow.
*
* @param int : value
* @exception : none
* @return bool : true on success, false on overflow
* @note : none
****************************/
    if (top >= STACK_SIZE - 1)
    {
        return false;
    }
    top++;
    data[top] = value;
    return true;
}

int Stack::pop()
{
/* **************************
* Removes and returns the top value of the stack.
* Throws an exception on underflow.
*
* @param : none
* @exception std::underflow_error : thrown if stack is empty
* @return int : the value removed from the top of the stack
* @note : none
****************************/
    if (isEmpty())
    {
        throw std::underflow_error("Stack underflow: cannot pop from an empty stack.");
    }
    int value = data[top];
    top--;
    return value;
}

int Stack::peek()
{
/* **************************
* Returns the top value of the stack without removing it.
* Throws an exception on underflow.
*
* @param : none
* @exception std::underflow_error : thrown if stack is empty
* @return int : the value at the top of the stack
* @note : none
****************************/
    if (isEmpty())
    {
        throw std::underflow_error("Stack underflow: cannot peek an empty stack.");
    }
    return data[top];
}
