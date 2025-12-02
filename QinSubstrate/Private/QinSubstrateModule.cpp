#include "QinSubstrateModule.h"
#include "Interfaces/IPluginManager.h"
#include "ShaderCore.h"

#define LOCTEXT_NAMESPACE "FQinSubstrateModule"

void FQinSubstrateModule::StartupModule()
{
    TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("QinSubstrate"));
    if (Plugin.IsValid())
    {
        FString ShaderDir = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Source/QinSubstrate/Shaders"));
        AddShaderSourceDirectoryMapping(TEXT("/QinSubstrate"), ShaderDir);
    }
}

void FQinSubstrateModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FQinSubstrateModule, QinSubstrate)
