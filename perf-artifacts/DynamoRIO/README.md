# DynamoRIO Tests Artifact Evaluation Guide

This guide provides step-by-step instructions for setting up and running DynamoRIO tests associated with the artifact evaluation of our research article.

## Prerequisites
- **MSVC Compiler**: Required for compiling C source files.

## Instructions

### Step 1: Compile the `transition_test` project.
Using Visual Studio (default MSVC compiler), compile the `transition_test` project.

### Step 2: Download pre-built DynamoRIO binaries
You can either build DynamoRIO or download the binary files from:
https://dynamorio.org/page_download.html

### Step 3: Download pre-built DynamoRIO binaries
You can either build DynamoRIO or download the binary files from:
https://dynamorio.org/page_download.html

### Step 4: Run DynamoRIO tool
Run the following command and wait for the script to complete and display the results.

```bash
.\bin64\drrun.exe -c .\samples\bin64\syscall.dll -- transition_test.exe
```
