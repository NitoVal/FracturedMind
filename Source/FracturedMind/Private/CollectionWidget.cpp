// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionWidget.h"

#include "CollectibleSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "FracturedMind/CollectibleData.h"
#include "FracturedMind/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

struct FCollectibleData;

void UCollectionWidget::NativeConstruct()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	for (ACollectible* Collectible : PlayerCharacter->Collectibles)
	{
		UCollectibleSlotWidget* ItemSlot = CreateWidget<UCollectibleSlotWidget>(this, CollectibleSlotClass);
		ItemSlot->SetCollectibleReference(Collectible);
		CollectionPanel->AddChildToWrapBox(ItemSlot);
	}
}
void UCollectionWidget::SetCollectibleText(ACollectible* CollectibleIn)
{
	FCollectibleData* Row = CollectibleIn->Collectible.GetRow<FCollectibleData>("Collectible Context");
	if (Row)
	{
		CollectibleNameText->SetText(Row->Name);
		CollectibleDescriptionText->SetText(Row->Description);
	}
}