#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnimGraphNode_Base.h"
#include "AnimNode_Mirroring.h"

#include "AnimGraphNode_Mirroring.generated.h"


// AnimGraphNode
UCLASS(meta = (Keywords = "Mirror, Mirroring"))
class ANIMMIRRORINGEDITOR_API UAnimGraphNode_Mirroring : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()
	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_Mirroring Node;
	
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
