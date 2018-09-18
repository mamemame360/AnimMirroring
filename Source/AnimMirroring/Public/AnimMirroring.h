#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"

class FAnimMirroringModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};