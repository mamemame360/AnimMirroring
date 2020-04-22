#pragma once

#include "CoreMinimal.h"
#include "AnimMirroringData.generated.h"


/** ミラーリングの軸 */
UENUM(BlueprintType)
enum class EMirrorAxis : uint8
{
	None,
	XAxis,
	YAxis,
	ZAxis,
};


/** ミラーリングするボーン名の指定規則 */
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


/** ミラーリングするポーン情報 */
USTRUCT(BlueprintType)
struct ANIMMIRRORING_API FMirrorMatchData
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMirrorAxis DefaultMirrorAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMirrorMatchData> MirrorMatches;
};
