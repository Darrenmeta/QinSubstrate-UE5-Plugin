#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"

USTRUCT(BlueprintType)
struct FQinParams
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Qin")
    float Eta = 0.02f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Qin")
    float Beta = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Qin")
    float Gamma = 0.35f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Qin")
    float UOn = 0.97f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Qin")
    float UOff = 0.03f;
};

class FQinCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FQinCS);
    SHADER_USE_PARAMETER_STRUCT(FQinCS, FGlobalShader);

public:
    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER(FVector2f, TextureSize)
        SHADER_PARAMETER(float, Eta)
        SHADER_PARAMETER(float, Beta)
        SHADER_PARAMETER(float, Gamma)
        SHADER_PARAMETER(float, UOn)
        SHADER_PARAMETER(float, UOff)

        SHADER_PARAMETER_TEXTURE(Texture2D, QinState)
        SHADER_PARAMETER_SAMPLER(SamplerState, QinSampler)

        SHADER_PARAMETER_TEXTURE(Texture2D, Mask)
        SHADER_PARAMETER_SAMPLER(SamplerState, MaskSampler)

        SHADER_PARAMETER_UAV(RWTexture2D<float>, OutTexture)
    END_SHADER_PARAMETER_STRUCT()

    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
    }
};

// Helper to dispatch the compute shader
void DispatchQinCS(
    FRHICommandListImmediate& RHICmdList,
    FTextureRHIRef QinStateTex,
    FTextureRHIRef MaskTex,
    FTextureRHIRef OutTex,
    const FQinParams& Params);
