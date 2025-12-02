using UnrealBuildTool;

public class QinSubstrate : ModuleRules
{
    public QinSubstrate(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "RenderCore",
                "RHI"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Projects",
                "Renderer"
            }
        );

        string ShaderDir = System.IO.Path.Combine(ModuleDirectory, "Shaders");
        AdditionalShaderDirectories.Add(ShaderDir);
    }
}
