#include "AnimMirroring.h"
#include "AnimMirroringLog.h"

#define LOCTEXT_NAMESPACE "FAnimMirroringModule"

void FAnimMirroringModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogAnimMirroring, Verbose, TEXT("FAnimMirroringModule::StartupModule"));
}

void FAnimMirroringModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogAnimMirroring, Verbose, TEXT("FAnimMirroringModule::StartupModule"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAnimMirroringModule, AnimMirroring)
