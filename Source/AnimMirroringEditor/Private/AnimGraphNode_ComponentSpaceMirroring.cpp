#include "AnimGraphNode_ComponentSpaceMirroring.h"
#include "AnimationGraphSchema.h"

#define LOCTEXT_NAMESPACE "FAnimMirroringEditorModule"

UAnimGraphNode_ComponentSpaceMirroring::UAnimGraphNode_ComponentSpaceMirroring(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

//Title Color!
FLinearColor UAnimGraphNode_ComponentSpaceMirroring::GetNodeTitleColor() const
{
	return FLinearColor(1.f, .55f, 0.f);
}

//Node Category
FString UAnimGraphNode_ComponentSpaceMirroring::GetNodeCategory() const
{
	return FString("AnimNode");
}
FString UAnimGraphNode_ComponentSpaceMirroring::GetControllerDescription() const
{
	return TEXT("ComponentSpaceMirroring");
}

FText UAnimGraphNode_ComponentSpaceMirroring::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FString Result = *GetControllerDescription();
	return FText::FromString(Result);
}


//Node Tooltip
FText UAnimGraphNode_ComponentSpaceMirroring::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_ComponentSpaceMirroring", "Mirroring pose.");
}

//Node Output Pin(Output is in Component Space, Change at own RISK!)
void UAnimGraphNode_ComponentSpaceMirroring::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("Pose"));
}

#undef LOCTEXT_NAMESPACE