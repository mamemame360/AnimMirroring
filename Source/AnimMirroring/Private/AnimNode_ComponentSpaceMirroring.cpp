#include "AnimNode_ComponentSpaceMirroring.h"
#include "AnimMirroringLog.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"


FAnimNode_ComponentSpaceMirroring::FAnimNode_ComponentSpaceMirroring()
	: FAnimNode_Base()
	, MirroringData(nullptr)
	, MirroringEnable(true)
{
}


void FAnimNode_ComponentSpaceMirroring::Initialize_AnyThread(const FAnimationInitializeContext & Context)
{
	ComponentPose.Initialize(Context);

	const FBoneContainer& BoneContainer = Context.AnimInstanceProxy->GetRequiredBones();

	ComponentSpaceRefPose.Reset();
	ComponentSpaceRefPose.Reserve(BoneContainer.GetCompactPoseNumBones());

	for (int32 iBone = 0; iBone < BoneContainer.GetCompactPoseNumBones(); iBone++) {
		FCompactPoseBoneIndex boneIndex(iBone);
		FTransform bonePose = BoneContainer.GetRefPoseTransform(boneIndex);

		FCompactPoseBoneIndex parentIndex = BoneContainer.GetParentBoneIndex(boneIndex);
		while (parentIndex.GetInt() != INDEX_NONE) {
			FTransform parentPose = BoneContainer.GetRefPoseTransform(parentIndex);
			bonePose = bonePose * parentPose;
			parentIndex = BoneContainer.GetParentBoneIndex(parentIndex);

		}
		ComponentSpaceRefPose.Add(bonePose);

	}

	MirrorInfo.Initialize(OverrideMirrorMatches, MirroringData, BoneContainer);
}


void FAnimNode_ComponentSpaceMirroring::CacheBones_AnyThread(const FAnimationCacheBonesContext & Context)
{
	ComponentPose.CacheBones(Context);
}


void FAnimNode_ComponentSpaceMirroring::Update_AnyThread(const FAnimationUpdateContext & Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}


void FAnimNode_ComponentSpaceMirroring::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output)
{
	Output.ResetToRefPose();
	ComponentPose.EvaluateComponentSpace(Output);
	if (!MirroringEnable) {
		return;
	}

	TArray<FTransform> CurrentTransforms;
	CurrentTransforms.Reserve(Output.Pose.GetPose().GetNumBones());

	// save current component space pose.
	// ループ中にSetComponentSpaceTransformを使うと、GetComponentSpaceTransformの戻ってくる値が更新されてしまうので
	// 先にすべてのポーズを保管しておく。
	for (int32 iBone = 0; iBone < Output.Pose.GetPose().GetNumBones(); iBone++) {
		FCompactPoseBoneIndex boneIndex(iBone);
		CurrentTransforms.Add(Output.Pose.GetComponentSpaceTransform(boneIndex));
	}

	// mirroring pose.
	for (int32 iPair = 0; iPair < MirrorInfo.Items.Num(); iPair++) {
		_MirrorComponentSpacePose(Output, CurrentTransforms, MirrorInfo.Items[iPair]);
	}
}


void FAnimNode_ComponentSpaceMirroring::_MirrorComponentSpacePose(FComponentSpacePoseContext& Output, const TArray<FTransform>& CurrentTransforms, const FMirrorInfoItem& Item)
{
	auto BoneIndexA = Item.IndexA;
	auto BoneIndexB = Item.IndexB;
	if (BoneIndexA >= 0 && BoneIndexB >= 0) {
		if (BoneIndexA != BoneIndexB) {
			// Pair bone mirroring
			FTransform btA = CurrentTransforms[BoneIndexA];
			FTransform btB = CurrentTransforms[BoneIndexB];

			btA.SetRotation(btA.GetRotation() * ComponentSpaceRefPose[BoneIndexA].GetRotation().Inverse());
			btB.SetRotation(btB.GetRotation() * ComponentSpaceRefPose[BoneIndexB].GetRotation().Inverse());

			FMirrorInfo::MirrorTransform(btA, Item.MirrorAxis);
			FMirrorInfo::MirrorTransform(btB, Item.MirrorAxis);

			Output.Pose.SetComponentSpaceTransform(FCompactPoseBoneIndex(BoneIndexA), FTransform(btB.GetRotation() * ComponentSpaceRefPose[BoneIndexA].GetRotation(), btB.GetTranslation()));
			Output.Pose.SetComponentSpaceTransform(FCompactPoseBoneIndex(BoneIndexB), FTransform(btA.GetRotation() * ComponentSpaceRefPose[BoneIndexB].GetRotation(), btA.GetTranslation()));
		}
		else {
			// single bone mirroring
			FTransform btA = CurrentTransforms[BoneIndexA];

			btA.SetRotation(btA.GetRotation() * ComponentSpaceRefPose[BoneIndexA].GetRotation().Inverse());

			FMirrorInfo::MirrorTransform(btA, Item.MirrorAxis);

			Output.Pose.SetComponentSpaceTransform(FCompactPoseBoneIndex(BoneIndexA), FTransform(btA.GetRotation() * ComponentSpaceRefPose[BoneIndexA].GetRotation(), btA.GetTranslation()));
		}
	}
}
