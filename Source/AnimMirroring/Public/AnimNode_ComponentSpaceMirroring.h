#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimationAsset.h"
#include "Animation/AnimNodeBase.h"
#include "AnimMirroringData.h"
#include "AnimMirroringInfo.h"

#include "AnimNode_ComponentSpaceMirroring.generated.h"


// Anim Behavior Node
USTRUCT(BlueprintInternalUseOnly)
struct ANIMMIRRORING_API FAnimNode_ComponentSpaceMirroring : public FAnimNode_Base
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FComponentSpacePoseLink ComponentPose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	UAnimMirroringData* MirroringData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	TArray<FMirrorMatchData> OverrideMirrorMatches;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))
	bool MirroringEnable;

protected:
	FMirrorInfo MirrorInfo;
	TArray<FTransform> ComponentSpaceRefPose;


public:
	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	//virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override;
	//virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	// End of FAnimNode_Base interface

public:
	FAnimNode_ComponentSpaceMirroring();

private:
	void _MirrorComponentSpacePose(FComponentSpacePoseContext& Output, const TArray<FTransform>& CurrentTransforms, const FMirrorInfoItem& Item);
};
