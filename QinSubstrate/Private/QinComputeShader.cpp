#include "QinComputeShader.h"
#include "RenderGraphBuilder.h"
#include "RenderGraphUtils.h"
#include "RHIStaticStates.h"

IMPLEMENT_GLOBAL_SHADER(FQinCS, "/QinSubstrate/QinCS.usf", "MainCS", SF_Compute);

void DispatchQinCS(
    FRHICommandListImmediate& RHICmdList,
    FTextureRHIRef QinStateTex,
    FTextureRHIRef MaskTex,
    FTextureRHIRef OutTex,
    const FQinParams& Params)
{
    check(IsInRenderingThread());

    FRDGBuilder GraphBuilder(RHICmdList);

    FRDGTextureRef QinTexRDG  = GraphBuilder.RegisterExternalTexture(CreateRenderTarget(QinStateTex, TEXT("QinStateRDG")));
    FRDGTextureRef MaskTexRDG = GraphBuilder.RegisterExternalTexture(CreateRenderTarget(MaskTex, TEXT("QinMaskRDG")));
    FRDGTextureRef OutTexRDG  = GraphBuilder.RegisterExternalTexture(CreateRenderTarget(OutTex, TEXT("QinOutRDG")));

    FQinCS::FParameters* PassParams = GraphBuilder.AllocParameters<FQinCS::FParameters>();

    FIntPoint Size = QinStateTex->GetTexture2D()->GetSizeXY();
    PassParams->TextureSize = FVector2f(Size.X, Size.Y);
    PassParams->Eta   = Params.Eta;
    PassParams->Beta  = Params.Beta;
    PassParams->Gamma = Params.Gamma;
    PassParams->UOn   = Params.UOn;
    PassParams->UOff  = Params.UOff;

    PassParams->QinState    = QinTexRDG;
    PassParams->QinSampler  = TStaticSamplerState<SF_Bilinear>::GetRHI();

    PassParams->Mask        = MaskTexRDG;
    PassParams->MaskSampler = TStaticSamplerState<SF_Point>::GetRHI();

    PassParams->OutTexture  = GraphBuilder.CreateUAV(FRDGTextureUAVDesc(OutTexRDG));

    TShaderMapRef<FQinCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

    FIntVector GroupCount(
        FMath::DivideAndRoundUp(Size.X, 8),
        FMath::DivideAndRoundUp(Size.Y, 8),
        1);

    GraphBuilder.AddPass(
        RDG_EVENT_NAME("QinCS"),
        PassParams,
        ERDGPassFlags::Compute,
        [PassParams, ComputeShader, GroupCount](FRHICommandList& RHICmdListInner)
        {
            FComputeShaderUtils::Dispatch(RHICmdListInner, ComputeShader, *PassParams, GroupCount);
        });

    GraphBuilder.Execute();
}
