#include "AnimNode_Mirroring.h"
#include "AnimMirroringLog.h"
#include <AnimationRuntime.h>
#include <Animation/AnimInstanceProxy.h>


FAnimNode_Mirroring::FAnimNode_Mirroring()
	: FAnimNode_Base()
	, MirroringData(nullptr)
	, MirroringEnable(true)
{
}



void FAnimNode_Mirroring::Initialize_AnyThread(const FAnimationInitializeContext & Context)
{
	BasePose.Initialize(Context);

	const FBoneContainer& BoneContainer = Context.AnimInstanceProxy->GetRequiredBones();

	MirrorInfo.Initialize(OverrideMirrorMatches, MirroringData, BoneContainer);
}


void FAnimNode_Mirroring::CacheBones_AnyThread(const FAnimationCacheBonesContext & Context)
{
	BasePose.CacheBones(Context);
}


void FAnimNode_Mirroring::Update_AnyThread(const FAnimationUpdateContext & Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	BasePose.Update(Context);
}


void FAnimNode_Mirroring::Evaluate_AnyThread(FPoseContext& Output)
{
	BasePose.Evaluate(Output);
	if (!MirroringEnable) {
		return;
	}

	for (int32 iPair = 0; iPair < MirrorInfo.Items.Num(); iPair++) {
		_MirrorPose(Output, MirrorInfo.Items[iPair]);
	}
}


void FAnimNode_Mirroring::_MirrorPose(FPoseContext& Output, const FMirrorInfoItem& Item)
{
	auto BoneIndexA = Item.IndexA;
	auto BoneIndexB = Item.IndexB;
	if (BoneIndexA >= 0 && BoneIndexB >= 0) {
		if (BoneIndexA != BoneIndexB) {
			FCompactPoseBoneIndex biA(BoneIndexA);
			FCompactPoseBoneIndex biB(BoneIndexB);
			FTransform btA = Output.Pose[biA];
			FTransform btB = Output.Pose[biB];

			FMirrorInfo::MirrorTransform(btA, Item.MirrorAxis);
			FMirrorInfo::MirrorTransform(btB, Item.MirrorAxis);

			Output.Pose[biA].SetRotation(btB.GetRotation());
			Output.Pose[biA].SetLocation(btB.GetLocation());
			Output.Pose[biB].SetRotation(btA.GetRotation());
			Output.Pose[biB].SetLocation(btA.GetLocation());
		}
		else {
			FCompactPoseBoneIndex biA(BoneIndexA);
			FTransform btA = Output.Pose[biA];

			FMirrorInfo::MirrorTransform(btA, Item.MirrorAxis);

			Output.Pose[biA].SetRotation(btA.GetRotation());
			Output.Pose[biA].SetLocation(btA.GetLocation());
		}
	}
}
