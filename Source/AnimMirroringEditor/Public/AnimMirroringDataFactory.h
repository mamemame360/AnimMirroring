#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AnimMirroringDataFactory.generated.h"

UCLASS()
class UAnimMirroringDataFactory : public UFactory
{
	GENERATED_BODY()

public:
	UAnimMirroringDataFactory(const FObjectInitializer& ObjectInitializer);

	virtual bool DoesSupportClass(UClass* Class) override;
	virtual UClass* ResolveSupportedClass() override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};