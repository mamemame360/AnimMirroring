#include "AnimMirroringData.h"


FMirrorMatchData::FMirrorMatchData()
	: NameRule(EMirroringNameRule::FullMatch)
	, BoneName()
	, PairBoneName()
	, MirrorAxis(EMirrorAxis::None)
{

}


FMirrorMatchData::FMirrorMatchData(EMirroringNameRule InNameRule, const FString& InBoneName, EMirrorAxis InMirrorAxis)
	: NameRule(InNameRule)
	, BoneName(InBoneName)
	, PairBoneName(InBoneName)
	, MirrorAxis(InMirrorAxis)
{

}


FMirrorMatchData::FMirrorMatchData(EMirroringNameRule InNameRule, const FString& InBoneName, const FString& InPairBoneName, EMirrorAxis InMirrorAxis)
	: NameRule(InNameRule)
	, BoneName(InBoneName)
	, PairBoneName(InPairBoneName)
	, MirrorAxis(InMirrorAxis)
{

}


UAnimMirroringData::UAnimMirroringData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, DefaultMirrorAxis(EMirrorAxis::None)
{

}
