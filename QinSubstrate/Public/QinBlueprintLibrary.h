#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QinComputeShader.h"
#include "Engine/TextureRenderTarget2D.h"
#include "QinBlueprintLibrary.generated.h"

UCLASS()
class QINSUBSTRATE_API UQinBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Qin")
    static void QinStep2D(
        UTextureRenderTarget2D* CurrentState,
        UTexture2D* Mask,
        UTextureRenderTarget2D* OutState,
        FQinParams Params);
};
