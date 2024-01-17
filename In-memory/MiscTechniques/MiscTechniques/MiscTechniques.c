#include <stdio.h>
#include "Techniques.h"

int main()
{
	UINT32 TargetProcessId = 0x1c0;

	// InjectShellcodeRemoteProcess(TargetProcessId);
	// DllInjectionRemoteProcess(TargetProcessId);
	// ReflectiveDllInjection();
	// RunFromPeResources();
	// ApcQueueCodeInjection();
	// EarlyBirdApcQueueInjection();
	// ExecuteModuleShellcodeUsingFiber();
	// ModuleExecutionThroughThreadPool();
	MapViewOfSectionCodeInjection(TargetProcessId);
}
