# Assignment 4: Simple Int Stack

## Description
A fixed-size integer Stack ADT implemented with a static array, built
to demonstrate proper ADT architecture, file separation, and
comprehensive developer testing.

## Files
- `stack.h` / `stack.cpp` — Stack ADT interface and implementation
- `main.h` / `main.cpp` — test driver (testbed); all testing lives in `main()`
- `essay.md` — required AI usage statement and essay

## Design
- The stack is backed by a static array of size `STACK_SIZE`
  (`const int`, defined in `stack.h`, default `10`).
- `top` tracks the index of the top element; an empty stack has
  `top < 0`.
- `pop()` and `peek()` report underflow by throwing
  `std::underflow_error`. `push()` returns `bool` and returns `false`
  on overflow rather than throwing, since it does not need to return a
  value to the caller.
- No public methods exist beyond `push`, `pop`, `peek`, and `isEmpty`.

## Testing
`main()` is the testbed and performs two phases:
1. **Explicit testing** — every operation is exercised in every
   reachable state: empty/underflow, normal push/pop/peek, full/overflow,
   and interleaved sequences.
2. **Random testing** — `STACK_SIZE * 100` random operations
   (1000 for the default size of 10) are run and verified against a
   parallel shadow stack maintained in `main()`.

Because every test loop bound is derived from `STACK_SIZE` rather than
a literal, the entire suite scales automatically if `STACK_SIZE` is
changed in `stack.h` — no other code changes are required. This was
verified by temporarily setting `STACK_SIZE` to `100` and confirming
all 10,000 random operations still passed.

## Build
```
g++ -std=c++17 -Wall -Wextra -o stacktest main.cpp stack.cpp
./stacktest
```

## Author
Aniketh Sriramoju
