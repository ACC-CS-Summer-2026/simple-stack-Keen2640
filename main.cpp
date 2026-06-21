/* *************************************************
*  Name: Aniketh Sriramoju
*  Assignment: Assignment 4
*  Purpose: Driver/testbed file to thoroughly test the Stack ADT
************************************************* */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "stack.h"
#include "main.h"

#define RANDOM_VALUE_RANGE 1000
#define NUM_OPERATIONS 4
#define RANDOM_MULTIPLIER 100

int main()
{
/* **************************
* Main testbed for the Stack class. Tests every operation
* (push, pop, peek, isEmpty) in every state (underflow,
* overflow, neither), explicitly and randomly, dynamically
* based on STACK_SIZE.
*
* @param : none
* @exception : none
* @return int : 0 on success
* @note : none
****************************/
    Stack s;
    int value;
    bool result;
    int i;
    int operation;
    int numRandomOps;

    // ---------- EXPLICIT TEST: isEmpty on a new stack ----------
    std::cout << "Test: new stack isEmpty: " << s.isEmpty() << std::endl;

    // ---------- EXPLICIT TEST: underflow on pop ----------
    try
    {
        value = s.pop();
        std::cout << "FAIL: pop on empty stack did not throw" << std::endl;
    }
    catch (const std::underflow_error& e)
    {
        std::cout << "PASS: pop underflow caught: " << e.what() << std::endl;
    }

    // ---------- EXPLICIT TEST: underflow on peek ----------
    try
    {
        value = s.peek();
        std::cout << "FAIL: peek on empty stack did not throw" << std::endl;
    }
    catch (const std::underflow_error& e)
    {
        std::cout << "PASS: peek underflow caught: " << e.what() << std::endl;
    }

    // ---------- EXPLICIT TEST: push one item, then peek (neither empty nor full) ----------
    result = s.push(42);
    std::cout << "Push single item: " << result << std::endl;
    value = s.peek();
    std::cout << "Peek single item: " << value << std::endl;
    std::cout << "isEmpty with one item: " << s.isEmpty() << std::endl;
    value = s.pop();
    std::cout << "Pop single item: " << value << std::endl;
    std::cout << "isEmpty after popping single item: " << s.isEmpty() << std::endl;

    // ---------- EXPLICIT TEST: fill stack to overflow ----------
    i = 0;
    while (i < STACK_SIZE)
    {
        result = s.push(i);
        std::cout << "Push " << i << " : " << result << std::endl;
        i++;
    }

    // ---------- EXPLICIT TEST: overflow ----------
    result = s.push(RANDOM_VALUE_RANGE);
    std::cout << "Push on full stack (overflow): " << result << std::endl;

    // ---------- EXPLICIT TEST: isEmpty on full stack ----------
    std::cout << "isEmpty on full stack: " << s.isEmpty() << std::endl;

    // ---------- EXPLICIT TEST: peek on full stack ----------
    value = s.peek();
    std::cout << "Peek on full stack: " << value << std::endl;

    // ---------- EXPLICIT TEST: pop one item off full stack, then peek (neither state) ----------
    value = s.pop();
    std::cout << "Pop from full stack: " << value << std::endl;
    value = s.peek();
    std::cout << "Peek after popping from full: " << value << std::endl;
    std::cout << "isEmpty after popping from full: " << s.isEmpty() << std::endl;

    // ---------- EXPLICIT TEST: pop everything remaining off ----------
    while (!s.isEmpty())
    {
        value = s.pop();
        std::cout << "Pop: " << value << std::endl;
    }

    // ---------- EXPLICIT TEST: confirm empty again ----------
    std::cout << "isEmpty after popping all: " << s.isEmpty() << std::endl;

    // ---------- RANDOM TESTING ----------
    numRandomOps = STACK_SIZE * RANDOM_MULTIPLIER;
    srand(static_cast<unsigned int>(time(nullptr)));

    Stack randomStack;
    i = 0;
    while (i < numRandomOps)
    {
        operation = rand() % NUM_OPERATIONS;

        if (operation == 0)
        {
            value = rand() % RANDOM_VALUE_RANGE;
            result = randomStack.push(value);
            std::cout << "Random push " << value << ": " << result << std::endl;
        }
        else if (operation == 1)
        {
            try
            {
                value = randomStack.pop();
                std::cout << "Random pop: " << value << std::endl;
            }
            catch (const std::underflow_error& e)
            {
                std::cout << "Random pop underflow: " << e.what() << std::endl;
            }
        }
        else if (operation == 2)
        {
            try
            {
                value = randomStack.peek();
                std::cout << "Random peek: " << value << std::endl;
            }
            catch (const std::underflow_error& e)
            {
                std::cout << "Random peek underflow: " << e.what() << std::endl;
            }
        }
        else
        {
            std::cout << "Random isEmpty: " << randomStack.isEmpty() << std::endl;
        }

        i++;
    }

    return 0;
}
