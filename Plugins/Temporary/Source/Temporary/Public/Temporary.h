#pragma once

#include "Modules/ModuleManager.h"

class FTemporaryModule : public IModuleInterface
{
public:
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
