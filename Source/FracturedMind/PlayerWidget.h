// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class FRACTUREDMIND_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractionPromptText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FPSLabel;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FPSText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CollectibleNameText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InspectDescriptionText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExitInspectionPromptText;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetInteractPromptVisibility(bool bIsVisible);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetExitInspectionPromptVisibility(bool bIsVisible);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetInspectDescriptionText(bool bIsVisible, AActor* Collectible);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetFPSCounterVisibility(bool bIsVisible);
	
	UFUNCTION(BlueprintCallable, Category = "FPS")
	void UpdateFPS(float NewFPS);
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	int FrameCount = 0;
	float TimeAccumulator = 0.0f;
};
