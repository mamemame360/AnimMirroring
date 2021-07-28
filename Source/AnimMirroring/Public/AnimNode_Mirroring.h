#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "AnimMirroringData.h"
#include "AnimMirroringInfo.h"

#include "AnimNode_Mirroring.generated.h"


// Anim Behavior Node
USTRUCT(BlueprintInternalUseOnly)
struct ANIMMIRRORING_API FAnimNode_Mirroring : public FAnimNode_Base
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FPoseLink BasePose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	UAnimMirroringData* MirroringData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	TArray<FMirrorMatchData> OverrideMirrorMatches;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))
	bool MirroringEnable;

protected:
	FMirrorInfo MirrorInfo;

public:
	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	//virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	// End of FAnimNode_Base interface

public:
	FAnimNode_Mirroring();

private:
	void _MirrorPose(FPoseContext& Output, const FMirrorInfoItem& Item);
};
