# QEMU Artifact Evaluation Guide

This guide provides step-by-step instructions for setting up, modifying, and testing QEMU as part of the artifact evaluation process for our research article.

## Important Information to Note
- **Register Usage**:
  - User-level applications pass arguments using `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, and `%r9`.
  - The kernel interface uses `%rdi`, `%rsi`, `%rdx`, `%r10`, `%r8`, and `%r9`.
- **Syscall Instruction**:
  - `%rcx` and `%r11` are clobbered, while `%rax` is used for the return value.
  - Syscalls are limited to six arguments with none passed directly on the stack.
- **Syscall Number**:
  - The number of the syscall should be placed in register `%rax`.

## Prerequisites
Ensure that the required development tools and libraries are installed (Use QEMU help for more information).

### Install Dependencies
Run the following command to install GTK development libraries:
```bash
sudo apt-get install libgtk-3-dev
```

## Cloning and Compiling QEMU
1. Clone the QEMU repository from GitHub:
   ```bash
   git clone https://github.com/qemu/qemu.git
   cd qemu
   ```

2. Configure QEMU with GTK support:
   ```bash
   ../configure --enable-gtk
   ```

## Modifying QEMU for Performance Measurement

### Function for `syscall`
Locate and modify the following file:
```
/qemu/qemu/target/i386/tcg/sysemu/seg_helper.c
```
The function to focus on:
```C
void helper_syscall(CPUX86State *env, int next_eip_addend)
```

### Function for `sysret` (Alternative Approach)
For an alternative, locate this function:
```
/qemu/qemu/target/i386/tcg/seg_helper.c
```
```C
void helper_sysret(CPUX86State *env, int dflag)
```

## Patching the `syscall` Function
Add the following code snippet to implement performance measurement:

### Code to Add
```C
//
// Global variables
//
int start_measuring_performance = 0;
uint64_t trm_start_tsc = 0;
uint64_t trm_stop_tsc = 0;

//
// Function definitions
//
uint64_t trm_rdtscp(void);
void performing_measurements(void);

uint64_t trm_rdtscp(void) {
    uint32_t lo, hi;

    // Assembly instruction for RDTSCP
    __asm__ volatile("rdtscp" : "=a" (lo), "=d" (hi) : : "%rcx");

    return ((uint64_t)hi << 32) | lo;
}

void performing_measurements(void) {
    if (start_measuring_performance == 0) {
        //
        // Start the measurements
        //
        start_measuring_performance = 1;
        trm_start_tsc = trm_rdtscp();
    } else {
        //
        // Stop the measurement
        //
        start_measuring_performance = 0;
        trm_stop_tsc = trm_rdtscp();
        
        printf("[*] the TSC difference is: %ld\n", (trm_stop_tsc - trm_start_tsc));
    }
}
```

### Modify `helper_syscall`
Insert the following code at the start of the `helper_syscall` function:
```C
if (env->regs[R_ECX] == 0x55558585 && env->regs[R_EAX] == 0x85855555) {
    printf("[*] Magic system-call called!\n");
    performing_measurements();
}
```

### Build QEMU
```bash
make
```

### Create Virtual Disc
Create a virtual disk using the following command.
```bash
./qemu-img create -f qcow2 ubuntu-disk.qcow2 40G
```

### Run QEMU
Download your favorite Linux distro and change the iso name in the following command and then run the following command.

```bash
./qemu-system-x86_64 -boot d -cdrom ~/Downloads/alpine-standard-3.20.3-x86_64.iso -m 3000 -drive file=ubuntu-disk.qcow2,format=qcow2 -smp 8
```

## Compiling `test.c` in the target machine
Use the following command to compile `test.c` into a static executable:
```bash
gcc -static -o test test.c
```

## Run `test` 
Run `test` and wait for the result to appear (in the command line of where you run the QEMU on the host).