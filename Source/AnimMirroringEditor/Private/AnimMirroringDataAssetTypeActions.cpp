#include "AnimMirroringDataAssetTypeActions.h"


FAnimMirroringDataAssetTypeActions::FAnimMirroringDataAssetTypeActions()
: FAssetTypeActions_Base()
{
}

FColor FAnimMirroringDataAssetTypeActions::GetTypeColor() const
{
	return FColor(0.5f, 0.5f, 0.5f);
}

void FAnimMirroringDataAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
}