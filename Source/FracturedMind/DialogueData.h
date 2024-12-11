#pragma once

#include "CoreMinimal.h"
#include "DialogueData.generated.h"

USTRUCT(BlueprintType)
struct FRACTUREDMIND_API FDialogueData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* AudioFile;   

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> ValidPositions;
};