// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CollectionWidget.generated.h"

class ACollectible;
class UCollectibleSlotWidget;
class UWrapBox;
class UTextBlock;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseCollectionAnimationFinished);
UCLASS()
class UCollectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UWrapBox* CollectionPanel;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CollectibleNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CollectibleDescriptionText;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCollectibleSlotWidget> CollectibleSlotClass;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OpeningCollectionAnimation;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ClosingCollectionAnimation;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnCloseCollectionAnimationFinished OnCloseAnimationFinished;
	
	void SetCollectibleText(ACollectible* CollectibleIn);
	void CloseCollectionUI();
protected:
	virtual void NativeConstruct() override;
};
