# Valgrind Tests Artifact Evaluation Guide

This guide provides step-by-step instructions for setting up and running Valgrind tests associated with the artifact evaluation of our research article.

## Prerequisites
- **VMWare Workstation**: Ensure that it is configured to run on a **single CPU core** for accurate test results.
- **GCC Compiler**: Required for compiling C source files.

## Instructions

### Step 1: Install valgrind
```
sudo apt install valgrind
```

### Step 2: Compile `test.c`
Compile the `test.c` file using the following command:
```bash
gcc -g -Og -std=gnu99 -static -o test_val test.c
```

### Step 3: Run valgrind
Navigate to the appropriate directory and execute valgrind:

```bash
valgrind ./test_val
```

Wait for the valgrind to complete and display the results.