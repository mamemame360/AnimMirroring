#pragma once

#include "CoreMinimal.h"
#include "AnimMirroringData.h"
#include "AnimMirroringInfo.generated.h"

struct FBoneContainer;

/** ミラーリング情報(内部使用) */
USTRUCT()
struct FMirrorInfoItem
{
	GENERATED_BODY()

	UPROPERTY()
	int32 IndexA;

	UPROPERTY()
	int32 IndexB;

	UPROPERTY()
	EMirrorAxis MirrorAxis;
};


/** ミラーリング情報(内部使用) */
USTRUCT()
struct FMirrorInfo
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FMirrorInfoItem> Items;

	void AddItems(const FMirrorMatchData& MatchData, const FBoneContainer& BoneContainer, TArray<int32>& ProcessedBones);
	void Initialize(const TArray<FMirrorMatchData>& OverrideMatches, const UAnimMirroringData* MirroringData, const FBoneContainer& BoneContainer);

	static void MirrorTransform(FTransform& Transform, EMirrorAxis MirrorAxis);

private:
	bool IsMatchBoneName(const FString& BoneName, const FString& MatchStr, bool HeadMatch);
	FString GetPairBoneName(const FString& BoneName, const FString& SourceMatchStr, const FString& TargetMatchStr, bool HeadMatch);
};