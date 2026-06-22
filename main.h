/*
 * File: main.h
 * Author: Aniketh Sriramoju
 * Date: June 21, 2026
 * Description: Constants used by main.cpp to drive comprehensive,
 *              size-independent testing of the Stack ADT. Keeping these
 *              values here instead of as literals in main.cpp means the
 *              test suite automatically scales if STACK_SIZE (in
 *              stack.h) is changed, with no other code changes needed.
 */

#ifndef MAIN_H
#define MAIN_H

// Number of random operations to run per unit of stack size.
// Follows the assignment guide's ratio: 1000 random ops for a stack
// of size 10, 10000 for size 100, and so on (size * 100).
const int RANDOM_OPS_MULTIPLIER = 100;

// Range of random integer values used during random push testing.
const int MIN_TEST_VALUE = -1000;
const int MAX_TEST_VALUE = 1000;
const int TEST_VALUE_RANGE = MAX_TEST_VALUE - MIN_TEST_VALUE + 1;

// Codes identifying which operation a random test iteration performs.
const int OP_PUSH = 0;
const int OP_POP = 1;
const int OP_PEEK = 2;
const int OP_ISEMPTY = 3;
const int NUM_OPERATIONS = 4;

// How often (in iterations) to print a progress update during random
// testing, so output stays readable even for very large stack sizes.
const int PROGRESS_INTERVAL = 500;

#endif
