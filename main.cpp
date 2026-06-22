/*
 * File: main.cpp
 * Author: Aniketh Sriramoju
 * Date: June 21, 2026
 * Description: Test driver (testbed) for the Stack ADT. Per assignment
 *              instructions, all testing logic lives directly in main()
 *              as one long function (modularity is intentionally not
 *              applied here). Testing proceeds in two stages:
 *                1) Explicit testing - every operation is exercised in
 *                   every reachable state (empty/underflow, normal,
 *                   full/overflow), including interleaved sequences.
 *                2) Random testing - a number of random operations
 *                   proportional to STACK_SIZE (STACK_SIZE * 100) are
 *                   executed against the stack and checked against a
 *                   parallel "shadow" reference structure to verify
 *                   correctness automatically.
 *              Because every loop bound below is driven by STACK_SIZE
 *              (defined once in stack.h) rather than a literal, this
 *              entire test suite scales automatically if STACK_SIZE is
 *              changed - with no other code changes required.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "stack.h"
#include "main.h"

/*
 * Function: main
 * Description: Drives explicit and random testing of the Stack ADT and
 *              reports a pass/fail summary to standard output.
 * Parameters: none
 * Return: int - 0 on completion
 */
int main() {
    Stack testStack;
    int shadowData[STACK_SIZE];
    int shadowTop;
    int testsPassed;
    int testsFailed;
    int i;
    int pushedValue;
    int poppedValue;
    int peekedValue;
    int expectedValue;
    bool pushResult;
    bool emptyResult;
    bool exceptionThrown;

    testsPassed = 0;
    testsFailed = 0;
    shadowTop = EMPTY_TOP;

    std::cout << "===== STACK ADT TEST SUITE (STACK_SIZE = " << STACK_SIZE
              << ") =====" << std::endl << std::endl;

    // ---------------------------------------------------------------
    // EXPLICIT TEST 1: a brand-new stack must be empty.
    // ---------------------------------------------------------------
    std::cout << "[Explicit] New stack isEmpty(): ";
    emptyResult = testStack.isEmpty();
    if (emptyResult == true) {
        testsPassed++;
        std::cout << "PASS" << std::endl;
    } else {
        testsFailed++;
        std::cout << "FAIL (expected true, got false)" << std::endl;
    }

    // ---------------------------------------------------------------
    // EXPLICIT TEST 2: pop() on an empty stack must throw underflow.
    // ---------------------------------------------------------------
    std::cout << "[Explicit] pop() on empty stack throws: ";
    exceptionThrown = false;
    try {
        poppedValue = testStack.pop();
    } catch (const std::underflow_error& e) {
        exceptionThrown = true;
    }
    if (exceptionThrown == true) {
        testsPassed++;
        std::cout << "PASS" << std::endl;
    } else {
        testsFailed++;
        std::cout << "FAIL (no exception thrown)" << std::endl;
    }

    // ---------------------------------------------------------------
    // EXPLICIT TEST 3: peek() on an empty stack must throw underflow.
    // ---------------------------------------------------------------
    std::cout << "[Explicit] peek() on empty stack throws: ";
    exceptionThrown = false;
    try {
        peekedValue = testStack.peek();
    } catch (const std::underflow_error& e) {
        exceptionThrown = true;
    }
    if (exceptionThrown == true) {
        testsPassed++;
        std::cout << "PASS" << std::endl;
    } else {
        testsFailed++;
        std::cout << "FAIL (no exception thrown)" << std::endl;
    }

    // ---------------------------------------------------------------
    // EXPLICIT TEST 4: fill the stack to exactly STACK_SIZE elements.
    // After every push, isEmpty() must be false and peek() must match
    // the value just pushed. Values are recorded into shadowData so
    // they can be verified again during the pop-all phase below.
    // ---------------------------------------------------------------
    std::cout << "[Explicit] Filling stack to capacity (" << STACK_SIZE
              << " pushes)..." << std::endl;
    for (i = 0; i < STACK_SIZE; i++) {
        pushedValue = i * 7;
        pushResult = testStack.push(pushedValue);
        shadowTop++;
        shadowData[shadowTop] = pushedValue;

        if (pushResult == false) {
            testsFailed++;
            std::cout << "  FAIL: push #" << i << " unexpectedly rejected" << std::endl;
        } else {
            testsPassed++;
        }

        emptyResult = testStack.isEmpty();
        if (emptyResult == true) {
            testsFailed++;
            std::cout << "  FAIL: isEmpty() true after push #" << i << std::endl;
        } else {
            testsPassed++;
        }

        peekedValue = testStack.peek();
        if (peekedValue == pushedValue) {
            testsPassed++;
        } else {
            testsFailed++;
            std::cout << "  FAIL: peek() returned " << peekedValue
                      << ", expected " << pushedValue << std::endl;
        }
    }
    std::cout << "  Fill phase complete." << std::endl;

    // ---------------------------------------------------------------
    // EXPLICIT TEST 5: pushing beyond capacity must fail (overflow)
    // and must not disturb the existing top value.
    // ---------------------------------------------------------------
    std::cout << "[Explicit] push() beyond capacity returns false: ";
    expectedValue = testStack.peek();
    pushResult = testStack.push(999);
    peekedValue = testStack.peek();
    if (pushResult == false && peekedValue == expectedValue) {
        testsPassed++;
        std::cout << "PASS" << std::endl;
    } else {
        testsFailed++;
        std::cout << "FAIL (push accepted or top value changed on overflow)" << std::endl;
    }

    // ---------------------------------------------------------------
    // EXPLICIT TEST 6: pop everything off and verify strict LIFO order
    // against the shadow array recorded during the fill phase.
    // ---------------------------------------------------------------
    std::cout << "[Explicit] Popping all elements, verifying LIFO order..." << std::endl;
    for (i = 0; i < STACK_SIZE; i++) {
        poppedValue = testStack.pop();
        expectedValue = shadowData[shadowTop];
        shadowTop--;

        if (poppedValue == expectedValue) {
            testsPassed++;
        } else {
            testsFailed++;
            std::cout << "  FAIL: pop() returned " << poppedValue
                      << ", expected " << expectedValue << std::endl;
        }
    }
    std::cout << "  Pop-all phase complete." << std::endl;

    // ---------------------------------------------------------------
    // EXPLICIT TEST 7: after popping everything, the stack is empty
    // again and pop()/peek() must once again throw underflow.
    // ---------------------------------------------------------------
    std::cout << "[Explicit] isEmpty() true after popping all: ";
    emptyResult = testStack.isEmpty();
    if (emptyResult == true) {
        testsPassed++;
        std::cout << "PASS" << std::endl;
    } else {
        testsFailed++;
        std::cout << "FAIL (expected true, got false)" << std::endl;
    }

    std::cout << "[Explicit] pop() throws again after re-emptying: ";
    exceptionThrown = false;
    try {
        poppedValue = testStack.pop();
    } catch (const std::underflow_error& e) {
        exceptionThrown = true;
    }
    if (exceptionThrown == true) {
        testsPassed++;
        std::cout << "PASS" << std::endl;
    } else {
        testsFailed++;
        std::cout << "FAIL (no exception thrown)" << std::endl;
    }

    // ---------------------------------------------------------------
    // EXPLICIT TEST 8: interleaved push/pop/peek sequence to confirm
    // the stack behaves correctly under mixed operations, not just
    // pure fill-then-drain patterns.
    // ---------------------------------------------------------------
    std::cout << "[Explicit] Interleaved push/pop/peek/isEmpty sequence: ";
    shadowTop = EMPTY_TOP;
    exceptionThrown = false;

    pushResult = testStack.push(10);
    shadowTop++;
    shadowData[shadowTop] = 10;

    pushResult = testStack.push(20);
    shadowTop++;
    shadowData[shadowTop] = 20;

    poppedValue = testStack.pop();
    expectedValue = shadowData[shadowTop];
    shadowTop--;
    if (poppedValue != expectedValue) {
        exceptionThrown = true;
    }

    pushResult = testStack.push(30);
    shadowTop++;
    shadowData[shadowTop] = 30;

    peekedValue = testStack.peek();
    if (peekedValue != shadowData[shadowTop]) {
        exceptionThrown = true;
    }

    poppedValue = testStack.pop();
    shadowTop--;
    poppedValue = testStack.pop();
    shadowTop--;
    emptyResult = testStack.isEmpty();
    if (emptyResult != true) {
        exceptionThrown = true;
    }

    if (exceptionThrown == false) {
        testsPassed++;
        std::cout << "PASS" << std::endl;
    } else {
        testsFailed++;
        std::cout << "FAIL (interleaved sequence produced unexpected state)" << std::endl;
    }

    // ---------------------------------------------------------------
    // RANDOM TESTING: exercise push, pop, peek, and isEmpty random
    // amounts of times, proportional to STACK_SIZE, and validate every
    // single operation against a parallel shadow stack. The number of
    // operations is STACK_SIZE * RANDOM_OPS_MULTIPLIER, so it scales
    // automatically if STACK_SIZE is changed in stack.h.
    // ---------------------------------------------------------------
    int totalRandomOps = STACK_SIZE * RANDOM_OPS_MULTIPLIER;
    int operationCode;
    bool shadowWasEmpty;
    bool iterationPassed;

    std::cout << std::endl << "[Random] Running " << totalRandomOps
              << " random operations..." << std::endl;

    shadowTop = EMPTY_TOP;
    std::srand(static_cast<unsigned int>(std::time(0)));

    for (i = 0; i < totalRandomOps; i++) {
        operationCode = std::rand() % NUM_OPERATIONS;
        iterationPassed = true;

        if (operationCode == OP_PUSH) {
            pushedValue = (std::rand() % TEST_VALUE_RANGE) + MIN_TEST_VALUE;
            pushResult = testStack.push(pushedValue);

            if (shadowTop >= STACK_SIZE - 1) {
                iterationPassed = (pushResult == false);
            } else {
                shadowTop++;
                shadowData[shadowTop] = pushedValue;
                iterationPassed = (pushResult == true);
            }
        } else if (operationCode == OP_POP) {
            shadowWasEmpty = (shadowTop <= EMPTY_TOP);
            exceptionThrown = false;
            try {
                poppedValue = testStack.pop();
            } catch (const std::underflow_error& e) {
                exceptionThrown = true;
            }

            if (shadowWasEmpty == true) {
                iterationPassed = (exceptionThrown == true);
            } else {
                expectedValue = shadowData[shadowTop];
                shadowTop--;
                iterationPassed = (exceptionThrown == false && poppedValue == expectedValue);
            }
        } else if (operationCode == OP_PEEK) {
            shadowWasEmpty = (shadowTop <= EMPTY_TOP);
            exceptionThrown = false;
            try {
                peekedValue = testStack.peek();
            } catch (const std::underflow_error& e) {
                exceptionThrown = true;
            }

            if (shadowWasEmpty == true) {
                iterationPassed = (exceptionThrown == true);
            } else {
                iterationPassed = (exceptionThrown == false && peekedValue == shadowData[shadowTop]);
            }
        } else {
            shadowWasEmpty = (shadowTop <= EMPTY_TOP);
            emptyResult = testStack.isEmpty();
            iterationPassed = (emptyResult == shadowWasEmpty);
        }

        if (iterationPassed == true) {
            testsPassed++;
        } else {
            testsFailed++;
            std::cout << "  FAIL at random iteration " << i
                       << " (operation code " << operationCode << ")" << std::endl;
        }

        if ((i + 1) % PROGRESS_INTERVAL == 0) {
            std::cout << "  ...completed " << (i + 1) << " / " << totalRandomOps
                       << " random operations" << std::endl;
        }
    }

    // ---------------------------------------------------------------
    // FINAL SUMMARY
    // ---------------------------------------------------------------
    std::cout << std::endl << "===== TEST SUMMARY =====" << std::endl;
    std::cout << "Total checks run: " << (testsPassed + testsFailed) << std::endl;
    std::cout << "Passed: " << testsPassed << std::endl;
    std::cout << "Failed: " << testsFailed << std::endl;

    if (testsFailed == 0) {
        std::cout << "RESULT: ALL TESTS PASSED" << std::endl;
    } else {
        std::cout << "RESULT: SOME TESTS FAILED - see FAIL lines above" << std::endl;
    }

    return 0;
}
