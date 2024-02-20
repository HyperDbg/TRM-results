#pragma once
#include <Windows.h>

VOID InjectShellcodeRemoteProcess(UINT32 ProcessId, unsigned char * Shellcode, unsigned int ShellcodeLen);

VOID DllInjectionRemoteProcess(UINT32 ProcessId);

VOID ReflectiveDllInjection();

VOID RunFromPeResources();

VOID ApcQueueCodeInjection();

VOID EarlyBirdApcQueueInjection();

VOID ExecuteModuleShellcodeUsingFiber();

VOID ModuleExecutionThroughThreadPool();

VOID MapViewOfSectionCodeInjection(UINT32 ProcessId);