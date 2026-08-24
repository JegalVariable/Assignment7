#include "Temporary.h"

#define LOCTEXT_NAMESPACE "FTemporaryModule"

void FTemporaryModule::StartupModule()
{
	UE_LOG(LogTemp, Log, TEXT("Temporary Module Started"));
}

void FTemporaryModule::ShutdownModule()
{
	UE_LOG(LogTemp, Log, TEXT("Temporary Module Shutdown"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTemporaryModule, Temporary)