#include "AnimMirroringInfo.h"
#include "AnimMirroringLog.h"
#include <AnimationRuntime.h>
#include <Animation/AnimInstanceProxy.h>

bool FMirrorInfo::IsMatchBoneName(const FString& BoneName, const FString& MatchStr, EMirroringNameRule MatchMode)
{
	const ESearchCase::Type SearchCase = ESearchCase::IgnoreCase;

	switch (MatchMode)
	{
	case EMirroringNameRule::HeadMatch:
		return BoneName.StartsWith(MatchStr, SearchCase);
	case EMirroringNameRule::TailMatch:
		return BoneName.EndsWith(MatchStr, SearchCase);
	case EMirroringNameRule::WordMatch:
		return BoneName.Contains(MatchStr);
	}
	checkNoEntry();
	return false;
}

FString FMirrorInfo::GetPairBoneName(const FString& BoneName, const FString& SourceMatchStr, const FString& TargetMatchStr, EMirroringNameRule MatchMode)
{
	switch (MatchMode)
	{
	case EMirroringNameRule::HeadMatch:
		return TargetMatchStr + BoneName.RightChop(SourceMatchStr.Len());
	case EMirroringNameRule::TailMatch:
		return BoneName.LeftChop(SourceMatchStr.Len()) + TargetMatchStr;
	case EMirroringNameRule::WordMatch:
		return BoneName.Replace(*SourceMatchStr, *TargetMatchStr);
	}
	checkNoEntry();
	return FString();
}

void FMirrorInfo::AddItems(const FMirrorMatchData& MatchData, const FBoneContainer& BoneContainer, TArray<int32>& ProcessedBones)
{
	const FString& boneName = MatchData.BoneName;
	const FString& pairBoneName = MatchData.PairBoneName;
	const EMirrorAxis mirrorAxis = MatchData.MirrorAxis;

	const bool validPairName = !pairBoneName.IsEmpty() && (boneName != pairBoneName);

	if (MatchData.NameRule == EMirroringNameRule::ExactMatch) {
		if (boneName.IsEmpty()) {
			return;
		}

		int32 iBone = BoneContainer.GetPoseBoneIndexForBoneName(*boneName);
		if (iBone < 0) {
			return;
		}

		if (ProcessedBones.Contains(iBone)) {
			return;
		}

		if (validPairName) {
			int32 iPairBone = BoneContainer.GetPoseBoneIndexForBoneName(*pairBoneName);
			if (iPairBone < 0) {
				return;
			}
			if (ProcessedBones.Contains(iPairBone)) {
				return;
			}

			ProcessedBones.Add(iBone);
			ProcessedBones.Add(iPairBone);
			UE_LOG(LogAnimMirroring, Verbose, TEXT("Pair Mirror Bone = %s %s"), *boneName, *pairBoneName);

			FMirrorInfoItem tmp;
			tmp.IndexA = iBone;
			tmp.IndexB = iPairBone;
			tmp.MirrorAxis = mirrorAxis;
			Items.Add(tmp);
		}
		else {
			ProcessedBones.Add(iBone);
			UE_LOG(LogAnimMirroring, Verbose, TEXT("Mirror Bone = %s"), *boneName);

			FMirrorInfoItem tmp;
			tmp.IndexA = iBone;
			tmp.IndexB = iBone;
			tmp.MirrorAxis = mirrorAxis;
			Items.Add(tmp);
		}
	}
	else if (MatchData.NameRule == EMirroringNameRule::Always) {
		for (int32 iBone = 0; iBone < BoneContainer.GetCompactPoseNumBones(); iBone++) {
			if (ProcessedBones.Contains(iBone)) {
				continue;
			}

			FMirrorInfoItem tmp;
			tmp.IndexA = iBone;
			tmp.IndexB = iBone;
			tmp.MirrorAxis = mirrorAxis;
			Items.Add(tmp);
		}
	}
	else if (MatchData.NameRule == EMirroringNameRule::HeadMatch || MatchData.NameRule == EMirroringNameRule::TailMatch || MatchData.NameRule == EMirroringNameRule::WordMatch) {
		if (boneName.IsEmpty()) {
			return;
		}

		for (int32 iBone = 0; iBone < BoneContainer.GetCompactPoseNumBones(); iBone++) {
			if (ProcessedBones.Contains(iBone)) {
				continue;
			}

			const FString skelBoneName = BoneContainer.GetReferenceSkeleton().GetBoneName(iBone).ToString();

			if (!IsMatchBoneName(skelBoneName, boneName, MatchData.NameRule)) {
				continue;
			}

			if (validPairName) {
				const FString skelPairBoneName = GetPairBoneName(skelBoneName, boneName, pairBoneName, MatchData.NameRule);

				int32 iPairBone = BoneContainer.GetPoseBoneIndexForBoneName(*skelPairBoneName);
				if (iPairBone < 0) {
					continue;
				}
				if (ProcessedBones.Contains(iPairBone)) {
					continue;
				}

				ProcessedBones.Add(iBone);
				ProcessedBones.Add(iPairBone);
				UE_LOG(LogAnimMirroring, Verbose, TEXT("Pair Mirror Bone = %s %s"), *skelBoneName, *skelPairBoneName);

				FMirrorInfoItem tmp;
				tmp.IndexA = iBone;
				tmp.IndexB = iPairBone;
				tmp.MirrorAxis = mirrorAxis;
				Items.Add(tmp);
			}
			else {
				ProcessedBones.Add(iBone);
				UE_LOG(LogAnimMirroring, Verbose, TEXT("Mirror Bone = %s"), *skelBoneName);

				FMirrorInfoItem tmp;
				tmp.IndexA = iBone;
				tmp.IndexB = iBone;
				tmp.MirrorAxis = mirrorAxis;
				Items.Add(tmp);
			}
		}
	}
}


void FMirrorInfo::Initialize(const TArray<FMirrorMatchData>& OverrideMatches, const UAnimMirroringData* MirroringData, const FBoneContainer& BoneContainer)
{
	Items.Reset();

	TArray<int32> processedBones;

	// 上書きのマッチ設定
	for (int32 iMatch = 0; iMatch < OverrideMatches.Num(); iMatch++) {
		AddItems(OverrideMatches[iMatch], BoneContainer, processedBones);
	}

	// アセットに設定されたマッチの設定
	if (MirroringData) {
		for (int32 iMatch = 0; iMatch < MirroringData->MirrorMatches.Num(); iMatch++) {
			AddItems(MirroringData->MirrorMatches[iMatch], BoneContainer, processedBones);
		}

		// 残ったボーンをすべて処理
		if (MirroringData->DefaultMirrorAxis != EMirrorAxis::None) {
			for (int32 iBone = 0; iBone < BoneContainer.GetCompactPoseNumBones(); iBone++) {
				if (processedBones.Contains(iBone)) {
					continue;
				}

				FMirrorInfoItem tmp;
				tmp.IndexA = iBone;
				tmp.IndexB = iBone;
				tmp.MirrorAxis = MirroringData->DefaultMirrorAxis;
				Items.Add(tmp);
			}
		}
	}
}


void FMirrorInfo::MirrorTransform(FTransform& Transform, EMirrorAxis MirrorAxis)
{
	auto _MirrorQuat = [](const FQuat& q, const FVector4& v) {
		return FQuat(q.X * v.X, q.Y * v.Y, q.Z * v.Z, q.W * v.W);
	};

	switch (MirrorAxis) {
	case EMirrorAxis::XAxis:
		Transform.SetLocation(Transform.GetLocation() * FVector(-1.0f, 1.0f, 1.0f));
		Transform.SetRotation(_MirrorQuat(Transform.GetRotation(), FVector4(-1.0f, 1.0f, 1.0f, -1.0f)));
		break;
	case EMirrorAxis::YAxis:
		Transform.SetLocation(Transform.GetLocation() * FVector(1.0f, -1.0f, 1.0f));
		Transform.SetRotation(_MirrorQuat(Transform.GetRotation(), FVector4(1.0f, -1.0f, 1.0f, -1.0f)));
		break;
	case EMirrorAxis::ZAxis:
		Transform.SetLocation(Transform.GetLocation() * FVector(1.0f, 1.0f, -1.0f));
		Transform.SetRotation(_MirrorQuat(Transform.GetRotation(), FVector4(1.0f, 1.0f, -1.0f, -1.0f)));
		break;
	}
}
