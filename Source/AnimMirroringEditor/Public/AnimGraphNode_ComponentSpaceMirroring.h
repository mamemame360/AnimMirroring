#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnimGraphNode_Base.h"
#include "AnimNode_ComponentSpaceMirroring.h"

#include "AnimGraphNode_ComponentSpaceMirroring.generated.h"


// AnimGraphNode
UCLASS(meta = (Keywords = "Mirror, Mirroring"))
class ANIMMIRRORINGEDITOR_API UAnimGraphNode_ComponentSpaceMirroring : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()
	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_ComponentSpaceMirroring Node;

public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FString GetNodeCategory() const override;
	virtual FText GetTooltipText() const override;
	virtual void CreateOutputPins() override;
	// End of UEdGraphNode interface

protected:
	virtual FString GetControllerDescription() const;	
	
};
