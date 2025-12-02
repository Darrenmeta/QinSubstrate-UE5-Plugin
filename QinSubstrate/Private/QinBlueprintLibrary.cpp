#include "QinBlueprintLibrary.h"
#include "Engine/Texture2D.h"
#include "RHICommandList.h"

void UQinBlueprintLibrary::QinStep2D(
    UTextureRenderTarget2D* CurrentState,
    UTexture2D* Mask,
    UTextureRenderTarget2D* OutState,
    FQinParams Params)
{
    if (!CurrentState || !Mask || !OutState)
    {
        UE_LOG(LogTemp, Warning, TEXT("QinStep2D: Missing textures"));
        return;
    }

    FTextureRenderTargetResource* CurrRes = CurrentState->GameThread_GetRenderTargetResource();
    FTextureRenderTargetResource* OutRes  = OutState->GameThread_GetRenderTargetResource();
    FTextureResource* MaskRes             = Mask->GetResource();

    if (!CurrRes || !OutRes || !MaskRes)
    {
        UE_LOG(LogTemp, Warning, TEXT("QinStep2D: Invalid resources"));
        return;
    }

    ENQUEUE_RENDER_COMMAND(QinStepCmd)(
        [CurrRes, OutRes, MaskRes, Params](FRHICommandListImmediate& RHICmdList)
        {
            FTextureRHIRef QinTex  = CurrRes->GetRenderTargetTexture();
            FTextureRHIRef OutTex  = OutRes->GetRenderTargetTexture();
            FTextureRHIRef MaskTex = MaskRes->TextureRHI;

            DispatchQinCS(RHICmdList, QinTex, MaskTex, OutTex, Params);
        });
}
