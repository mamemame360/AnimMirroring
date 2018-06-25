#pragma once

#include "CoreMinimal.h"
#include "AnimMirroringData.generated.h"


/** ミラーリングの軸 */
UENUM()
enum class EMirrorAxis : uint8
{
	None,
	Default,
	XAxis,
	YAxis,
	ZAxis,
};


/** ミラーリングするボーン名の指定規則 */
UENUM()
enum class EMirroringNameRule
{
	FullMatch,	//<! 完全一致
	HeadMatch,	//<! 前方一致
	TailMatch		// ! 後方一致
};


/** ミラーリングするポーン情報 */
USTRUCT(BlueprintType)
struct FMirrorMatchData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMirroringNameRule NameRule;	//!< ボーン名の指定規則

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BoneName;	//!< 対象ボーンの名前

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PairBoneName;	//!< ミラーリングする時の対になるボーンの名前(省略した場合は単独でミラーリングする)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMirrorAxis MirrorAxis;	//!< ミラーリングの軸

	FMirrorMatchData();
	FMirrorMatchData(EMirroringNameRule InNameRule, const FString& InBoneName, EMirrorAxis InMirrorAxis);
	FMirrorMatchData(EMirroringNameRule InNameRule, const FString& InBoneName, const FString& InPairBoneName, EMirrorAxis InMirrorAxis);
};


/** ミラーリング用データ */
UCLASS()
class ANIMMIRRORING_API UAnimMirroringData : public UObject
{
	GENERATED_BODY()

public:
	UAnimMirroringData(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	TArray<FMirrorMatchData> MirrorMatches;
};


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

	void AddItems(const FMirrorMatchData& MatchData, const FBoneContainer& BoneContainer, EMirrorAxis DefaultMirrorAxis, TArray<int32>& ProcessedBones);
	void Initialize(const TArray<FMirrorMatchData>& OverrideMatches, const UAnimMirroringData* MirroringData, const FBoneContainer& BoneContainer, EMirrorAxis DefaultMirrorAxis);

	static void MirrorTransform(FTransform& Transform, EMirrorAxis MirrorAxis);

private:
	bool IsMatchBoneName(const FString& BoneName, const FString& MatchStr, bool HeadMatch);
	FString GetPairBoneName(const FString& BoneName, const FString& SourceMatchStr, const FString& TargetMatchStr, bool HeadMatch);
};