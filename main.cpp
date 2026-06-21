/*****************************************************************
 * File: main.cpp
 * Author: Aniketh Sriramoju
 * Date: June 21, 2026
 * Description: Test driver (testbed) for the Stack ADT. Performs
 *              explicit tests of every operation in every state
 *              (empty, partial, full), then performs randomized
 *              testing scaled to STACK_SIZE, verifying every
 *              operation against a parallel "shadow" stack.
 *****************************************************************/

#include "main.h"

const int NUM_OPERATION_TYPES = 4;     // push, pop, peek, isEmpty
const int RANDOM_OPS_MULTIPLIER = 1000;
const int MAX_RANDOM_TEST_VALUE = 1000;
const int OVERFLOW_TEST_VALUE = 999;
const int MIXED_TEST_MULTIPLIER = 10;

/*****************************************************************
 * Function: main
 * Description: Drives all testing of the Stack ADT.
 * Parameters: none
 * Returns: int - 0 on successful completion of all tests
 *****************************************************************/
int main() {
    Stack stack;

    int shadowArray[STACK_SIZE];
    int shadowTop = -1;

    int i;
    int value;
    int randomOperations;
    int operationCount;
    int randomChoice;
    int randomValue;
    int passCount = 0;
    int failCount = 0;

    bool pushed;
    bool expectedFull;
    bool expectedEmpty;
    bool stackHasItems;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "===== EXPLICIT TEST 1: New stack should be empty =====\n";
    if (stack.isEmpty()) {
        std::cout << "PASS: isEmpty() true on new stack.\n";
    } else {
        std::cout << "FAIL: isEmpty() false on new stack.\n";
    }

    std::cout << "\n===== EXPLICIT TEST 2: pop()/peek() on empty stack (underflow) =====\n";
    try {
        value = stack.pop();
        std::cout << "FAIL: pop() did not throw on empty stack.\n";
    } catch (const StackException &e) {
        std::cout << "PASS: pop() threw underflow exception: " << e.what() << "\n";
    }

    try {
        value = stack.peek();
        std::cout << "FAIL: peek() did not throw on empty stack.\n";
    } catch (const StackException &e) {
        std::cout << "PASS: peek() threw underflow exception: " << e.what() << "\n";
    }

    std::cout << "\n===== EXPLICIT TEST 3: push() until full (fills STACK_SIZE = "
              << STACK_SIZE << ") =====\n";
    for (i = 0; i < STACK_SIZE; i++) {
        if (stack.push(i)) {
            shadowTop++;
            shadowArray[shadowTop] = i;
            std::cout << "PASS: pushed " << i << " (slot " << i << ").\n";
        } else {
            std::cout << "FAIL: push(" << i << ") failed unexpectedly.\n";
        }
    }

    std::cout << "\n===== EXPLICIT TEST 4: push() on full stack (overflow) =====\n";
    if (!stack.push(OVERFLOW_TEST_VALUE)) {
        std::cout << "PASS: push() correctly rejected overflow.\n";
    } else {
        std::cout << "FAIL: push() accepted a value past capacity.\n";
        shadowTop++;
        shadowArray[shadowTop] = OVERFLOW_TEST_VALUE;
    }

    std::cout << "\n===== EXPLICIT TEST 5: peek() returns top without removing =====\n";
    value = stack.peek();
    if (value == shadowArray[shadowTop]) {
        std::cout << "PASS: peek() returned " << value << " as expected.\n";
    } else {
        std::cout << "FAIL: peek() returned " << value << ", expected "
                  << shadowArray[shadowTop] << ".\n";
    }
    if (!stack.isEmpty()) {
        std::cout << "PASS: isEmpty() still false after peek().\n";
    } else {
        std::cout << "FAIL: isEmpty() true after peek() on full stack.\n";
    }

    std::cout << "\n===== EXPLICIT TEST 6: pop() all values off (LIFO order) =====\n";
    for (i = 0; i < STACK_SIZE; i++) {
        value = stack.pop();
        if (value == shadowArray[shadowTop]) {
            std::cout << "PASS: pop() returned " << value << " as expected.\n";
        } else {
            std::cout << "FAIL: pop() returned " << value << ", expected "
                      << shadowArray[shadowTop] << ".\n";
        }
        shadowTop--;
    }

    std::cout << "\n===== EXPLICIT TEST 7: stack empty again after popping all =====\n";
    if (stack.isEmpty()) {
        std::cout << "PASS: isEmpty() true after popping everything off.\n";
    } else {
        std::cout << "FAIL: isEmpty() false after popping everything off.\n";
    }

    std::cout << "\n===== EXPLICIT TEST 8: mixed push/pop/peek combination =====\n";
    for (i = 0; i < STACK_SIZE / 2; i++) {
        stack.push(i * MIXED_TEST_MULTIPLIER);
        shadowTop++;
        shadowArray[shadowTop] = i * MIXED_TEST_MULTIPLIER;
    }
    value = stack.pop();
    if (value == shadowArray[shadowTop]) {
        std::cout << "PASS: pop() in mixed sequence returned " << value << ".\n";
    } else {
        std::cout << "FAIL: pop() in mixed sequence returned " << value << ".\n";
    }
    shadowTop--;
    stack.push(OVERFLOW_TEST_VALUE - 222);
    shadowTop++;
    shadowArray[shadowTop] = OVERFLOW_TEST_VALUE - 222;
    value = stack.peek();
    if (value == shadowArray[shadowTop]) {
        std::cout << "PASS: peek() in mixed sequence returned " << value << ".\n";
    } else {
        std::cout << "FAIL: peek() in mixed sequence returned " << value << ".\n";
    }

    stackHasItems = !stack.isEmpty();
    while (stackHasItems) {
        stack.pop();
        shadowTop--;
        stackHasItems = !stack.isEmpty();
    }

    std::cout << "\n===== RANDOM TESTING: scaled to STACK_SIZE =====\n";
    randomOperations = STACK_SIZE * RANDOM_OPS_MULTIPLIER;
    std::cout << "Running " << randomOperations << " random operations...\n";

    for (operationCount = 0; operationCount < randomOperations; operationCount++) {
        randomChoice = std::rand() % NUM_OPERATION_TYPES;

        if (randomChoice == 0) {
            randomValue = std::rand() % MAX_RANDOM_TEST_VALUE;
            expectedFull = (shadowTop >= STACK_SIZE - 1);
            pushed = stack.push(randomValue);
            if (pushed == !expectedFull) {
                passCount++;
                if (pushed) {
                    shadowTop++;
                    shadowArray[shadowTop] = randomValue;
                }
            } else {
                failCount++;
            }
        } else if (randomChoice == 1) {
            expectedEmpty = (shadowTop < 0);
            try {
                value = stack.pop();
                if (!expectedEmpty && value == shadowArray[shadowTop]) {
                    shadowTop--;
                    passCount++;
                } else {
                    failCount++;
                }
            } catch (const StackException &) {
                if (expectedEmpty) {
                    passCount++;
                } else {
                    failCount++;
                }
            }
        } else if (randomChoice == 2) {
            expectedEmpty = (shadowTop < 0);
            try {
                value = stack.peek();
                if (!expectedEmpty && value == shadowArray[shadowTop]) {
                    passCount++;
                } else {
                    failCount++;
                }
            } catch (const StackException &) {
                if (expectedEmpty) {
                    passCount++;
                } else {
                    failCount++;
                }
            }
        } else {
            expectedEmpty = (shadowTop < 0);
            if (stack.isEmpty() == expectedEmpty) {
                passCount++;
            } else {
                failCount++;
            }
        }
    }

    std::cout << "Random testing complete. Passed: " << passCount
              << "  Failed: " << failCount << "\n";

    std::cout << "\n===== ALL TESTS COMPLETE =====\n";

    return 0;
}
