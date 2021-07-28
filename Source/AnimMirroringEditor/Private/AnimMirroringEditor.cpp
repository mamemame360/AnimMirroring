#include "AnimMirroringEditor.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AnimMirroringDataAssetTypeActions.h"

#define LOCTEXT_NAMESPACE "FAnimMirroringEditorModule"

void FAnimMirroringEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	TSharedPtr<IAssetTypeActions> actionType = MakeShareable(new FAnimMirroringDataAssetTypeActions());
	AssetTools.RegisterAssetTypeActions(actionType.ToSharedRef());
}

void FAnimMirroringEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAnimMirroringEditorModule, AnimMirroringEditor)