/* *************************************************
*  Name: Aniketh Sriramoju
*  Assignment: Assignment 4
*  Purpose: Class declaration file for an integer Stack ADT
************************************************* */

#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 10

class Stack
{
    /**********************
    * Constructors/Destructor
    ***********************/
public:
    Stack();

    /**********************
    * Getters/Accessors
    ***********************/
    int peek();
    bool isEmpty();

    /**********************
    * Setters/Mutators
    ***********************/
    bool push(int value);
    int pop();

    /**********************
    * Printing Methods
    ***********************/

private:
    /**********************
    * Methods
    ***********************/

    /**********************
    * Attributes
    ***********************/
    int data[STACK_SIZE];
    int top;
};

#endif // STACK_H
