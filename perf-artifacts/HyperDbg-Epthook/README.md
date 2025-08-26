# HyperDbg EPTHook Tests Artifact Evaluation Guide

This guide provides step-by-step instructions for setting up and running HyperDbg EPTHook tests associated with the artifact evaluation of our research article.

## Prerequisites
- **MSVC Compiler**: Required for compiling C source files.

## Instructions

### Step 1: Compile the `transition_test` project from the 'baremetal' directory.
Using Visual Studio (default MSVC compiler), compile the `transition_test` project. Start `transition_test.exe` and save the process ID (hex), we'll use it later in our scripts.

### Step 2: Run HyperDbg in the VMI mode
Follow the instructions here: https://docs.hyperdbg.org/getting-started/build-and-install
Run HyperDbg in the VMI mode

### Step 3: Run the following command in HyperDbg
Replace the process ID with the `0x3388` in the following script and then run it.

```C
? .test_var = 0;

!epthook nt!KiSystemCall64+3 pid 0x3388 script {
	//
	// Your target script here
	//
	.test_var = .test_var + 1;
}
```

### Step 4: Run the Test file
Navigate to the `transition_test.exe`, press 'Enter' and wait for the script to complete and display the results.
