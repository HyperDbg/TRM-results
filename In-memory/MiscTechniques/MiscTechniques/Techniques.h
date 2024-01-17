#pragma once
#include <Windows.h>

VOID InjectShellcodeRemoteProcess(UINT32 ProcessId);

VOID DllInjectionRemoteProcess(UINT32 ProcessId);

VOID ReflectiveDllInjection();

VOID RunFromPeResources();

VOID ApcQueueCodeInjection();

VOID EarlyBirdApcQueueInjection();