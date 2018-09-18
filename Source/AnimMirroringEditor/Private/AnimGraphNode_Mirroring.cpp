#include "AnimGraphNode_Mirroring.h"
#include "AnimationGraphSchema.h"

#define LOCTEXT_NAMESPACE "FAnimMirroringEditorModule"

UAnimGraphNode_Mirroring::UAnimGraphNode_Mirroring(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

//Title Color!
FLinearColor UAnimGraphNode_Mirroring::GetNodeTitleColor() const
{
	return FLinearColor(1.f, .55f, 0.f);
}

//Node Category
FString UAnimGraphNode_Mirroring::GetNodeCategory() const
{
	return FString("AnimNode");
}
FString UAnimGraphNode_Mirroring::GetControllerDescription() const
{
	return TEXT("Mirroring");
}

FText UAnimGraphNode_Mirroring::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FString Result = *GetControllerDescription();
	return FText::FromString(Result);
}


//Node Tooltip
FText UAnimGraphNode_Mirroring::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_Mirroring", "Mirroring pose.");
}

//Node Output Pin(Output is in Component Space, Change at own RISK!)
void UAnimGraphNode_Mirroring::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FPoseLink::StaticStruct(), TEXT("Pose"));
}

#undef LOCTEXT_NAMESPACE