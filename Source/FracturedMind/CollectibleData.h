#pragma once

#include "CoreMinimal.h"
#include "CollectibleData.generated.h"

USTRUCT(BlueprintType)
struct FRACTUREDMIND_API FCollectibleData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* CollectibleModel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterial* ModelMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;
};