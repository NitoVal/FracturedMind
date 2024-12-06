// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CollectibleSlotWidget.generated.h"

class UButton;
class UImage;
class UBorder;
class ACollectible;
/**
 * 
 */
UCLASS()
class UCollectibleSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetCollectibleReference(ACollectible* CollectibleIn) { CollectibleReference = CollectibleIn; }
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	UPROPERTY(VisibleAnywhere, Category="Inventory Slot")
	ACollectible* CollectibleReference;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UBorder* CollectibleBorder;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* CollectibleIcon;
};
