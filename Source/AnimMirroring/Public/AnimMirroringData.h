#pragma once

#include "CoreMinimal.h"
#include "AnimMirroringData.generated.h"


/** mirroring axis */
UENUM(BlueprintType)
enum class EMirrorAxis : uint8
{
	None,
	XAxis,
	YAxis,
	ZAxis,
};


/** bone name matching rule */
UENUM(BlueprintType)
enum class EMirroringNameRule : uint8
{
	// 常に不一致
	Never,
	// 常に一致
	Always,
	// 完全对应
	ExactMatch,
	// 前缀对应
	HeadMatch,
	// 后缀对应
	TailMatch,
	// 单词对应
	WordMatch
};


/** Bone Matching Data */
USTRUCT(BlueprintType)
struct ANIMMIRRORING_API FMirrorMatchData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMirroringNameRule NameRule;	//!< matching rule

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BoneName;	//!< target bone name

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PairBoneName;	//!< pair bone name.(if empty, mirrored alone.)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMirrorAxis MirrorAxis;	//!< mirroring axis.

	FMirrorMatchData();
	FMirrorMatchData(EMirroringNameRule InNameRule, const FString& InBoneName, EMirrorAxis InMirrorAxis);
	FMirrorMatchData(EMirroringNameRule InNameRule, const FString& InBoneName, const FString& InPairBoneName, EMirrorAxis InMirrorAxis);
};


/** mirroring data */
UCLASS(BlueprintType)
class ANIMMIRRORING_API UAnimMirroringData : public UObject
{
	GENERATED_BODY()

public:
	UAnimMirroringData(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMirrorAxis DefaultMirrorAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMirrorMatchData> MirrorMatches;
};
