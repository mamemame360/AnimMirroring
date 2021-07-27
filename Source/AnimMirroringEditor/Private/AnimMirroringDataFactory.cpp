#include "AnimMirroringDataFactory.h"
#include "AnimMirroringData.h"

UAnimMirroringDataFactory::UAnimMirroringDataFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UAnimMirroringData::StaticClass();
}


bool UAnimMirroringDataFactory::DoesSupportClass(UClass* Class)
{
	return (Class == UAnimMirroringData::StaticClass());
}


UClass* UAnimMirroringDataFactory::ResolveSupportedClass()
{
	return UAnimMirroringData::StaticClass();
}


UObject* UAnimMirroringDataFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UAnimMirroringData* MirroringData = NewObject<UAnimMirroringData>(InParent, InName, Flags);

	if (!MirroringData) {
		return nullptr;
	}

	MirroringData->DefaultMirrorAxis = EMirrorAxis::XAxis;
	MirroringData->MirrorMatches.Add(FMirrorMatchData(EMirroringNameRule::TailMatch, TEXT("_l"), TEXT("_r"), EMirrorAxis::XAxis));

	return MirroringData;
}