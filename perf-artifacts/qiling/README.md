# Qiling Tests Artifact Evaluation Guide

This guide provides step-by-step instructions for setting up and running the Qiling framework tests associated with the artifact evaluation of our research article.

## Prerequisites
- **VMWare Workstation**: Ensure that it is configured to run on a **single CPU core** for accurate test results.
- **GCC Compiler**: Required for compiling C source files.
- **Python**: Ensure Python is installed to run the Python script.

## Instructions

### Step 1: Compile `librdtscp.c`
Compile the `librdtscp.c` file to generate the shared library using the following command:
```bash
gcc -shared -o librdtscp.so -fPIC librdtscp.c
```

### Step 2: Move `test.c`
Place the `test.c` file into the following directory:
```
/qiling/qiling/examples/rootfs/x86_linux
```

### Step 3: Compile `test.c`
Compile `test.c` using the command below to create a static executable:
```bash
gcc -static -o test test.c
```

### Step 4: Move `qiling_test.py`
Transfer the `qiling_test.py` script to the following location within the Qiling framework:
```
/qiling/qiling/examples
```

### Step 5: Run the Python Test Script
Navigate to the appropriate directory and execute the script:
```bash
python qiling_test.py
```
Wait for the script to complete and display the results.