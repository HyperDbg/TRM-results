#include <stdio.h>
#include "Techniques.h"

//
// The techniques mentioned in this project are all derived from: https://www.ired.team
//

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
