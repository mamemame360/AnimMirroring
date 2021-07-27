#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "AnimMirroringData.h"


class FAnimMirroringDataAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FAnimMirroringDataAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);

	virtual FColor GetTypeColor() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	virtual FText GetName() const override { return FText::FromName(TEXT("AnimMirroringDataAsset")); }
	virtual UClass* GetSupportedClass() const override { return UAnimMirroringData::StaticClass(); }
	virtual uint32 GetCategories() override { return MyAssetCategory; }

private:
	EAssetTypeCategories::Type MyAssetCategory;
};
