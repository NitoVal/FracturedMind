// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleSlotWidget.h"

#include "Collectible.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "FracturedMind/CollectibleData.h"
#include "FracturedMind/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCollectibleSlotWidget::NativeConstruct()
{
	if (CollectibleReference)
	{
		FCollectibleData* Row = CollectibleReference->Collectible.GetRow<FCollectibleData>("Collectible Context");
		if (Row)
		{
			CollectibleIcon->SetBrushFromTexture(Row->Icon);
		}
	}
}

void UCollectibleSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	CollectibleBorder->SetBrushColor(FLinearColor::Yellow);
}

void UCollectibleSlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	CollectibleBorder->SetBrushColor(FLinearColor::Black);
}

FReply UCollectibleSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		PlayerCharacter->CollectionWidget->SetCollectibleText(CollectibleReference);
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
