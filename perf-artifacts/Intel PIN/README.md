# Intel PIN Tests Artifact Evaluation Guide

This guide provides step-by-step instructions for setting up and running the Intel PIN tests for the artifact evaluation of our research article.

## Prerequisites
- **VMWare Workstation**: Ensure that it is configured to run on a **single CPU core** for accurate test results.
- **GCC Compiler**: Required for compiling C source files.

## Instructions

### Step 1: Navigate to the Insmix Directory
Navigate to the following directory in your PIN installation:
```
/pin/pin-external-[VERSION]/source/tools/Insmix
```

### Step 2: Patch the Tool
Move the files from the `pin tool` directory to this location to patch the tool.

### Step 3: Compile the PIN Tool
Run the following command in the `Insmix` directory to compile the tool:
```bash
make
```

### Step 4: Move `test.c`
Place the `test.c` file into the following directory:
```
/pin/pin-external-[VERSION]/
```

### Step 5: Compile `test.c`
Compile `test.c` using the command below to create a static executable:
```bash
gcc -static -o test test.c
```

### Step 6: Run the PIN Tool
Navigate back to the main directory:
```
/pin/pin-external-[VERSION]/
```
Run the compiled PIN tool using the following command:
```bash
./pin -t source/tools/Insmix/obj-intel64/insmix.so -- ~/Desktop/qiling/qiling/examples/rootfs/x86_linux/test
```

Wait for the tool to complete and observe the results.