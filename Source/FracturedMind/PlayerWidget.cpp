// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

#include "CollectibleData.h"
#include "Private/Collectible.h"
#include "Components/TextBlock.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (FPSText->IsVisible())
	{
		FrameCount++;
		TimeAccumulator += InDeltaTime;

		if (TimeAccumulator >= 1.0f)
		{
			const int CurrentFPS = FrameCount / TimeAccumulator;
			UpdateFPS(CurrentFPS);
			
			FrameCount = 0;
			TimeAccumulator = 0.0f;
		}
	}
}

void UPlayerWidget::SetInteractPromptVisibility(bool bIsVisible)
{
	if (InteractionPromptText)
	{
		const ESlateVisibility DesiredVisibility  = bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
		InteractionPromptText->SetVisibility(DesiredVisibility);
	}
}

void UPlayerWidget::SetExitInspectionPromptVisibility(bool bIsVisible)
{
	if (ExitInspectionPromptText)
	{
		ESlateVisibility DesiredVisibility  = bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
		ExitInspectionPromptText->SetVisibility(DesiredVisibility);
	}
}

void UPlayerWidget::SetInspectDescriptionText(bool bIsVisible, AActor* Collectible)
{
	if (InspectDescriptionText && CollectibleNameText)
	{
		const ESlateVisibility DesiredVisibility  = bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
		CollectibleNameText->SetVisibility(DesiredVisibility);
		InspectDescriptionText->SetVisibility(DesiredVisibility);
		
		if (bIsVisible && Collectible)
		{
			ACollectible* CurrentCollectible = Cast<ACollectible>(Collectible);
			if (CurrentCollectible)
			{
				CollectibleNameText->SetText(CurrentCollectible->Collectible.GetRow<FCollectibleData>("Collectible Data")->Name);
				InspectDescriptionText->SetText(CurrentCollectible->Collectible.GetRow<FCollectibleData>("Collectible Data")->Description);
			}
		}
	}
}

void UPlayerWidget::SetFPSCounterVisibility(bool bIsVisible)
{
	if (FPSText && FPSLabel)
	{
		ESlateVisibility DesiredVisibility  = bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
		FPSLabel->SetVisibility(DesiredVisibility);
		FPSText->SetVisibility(DesiredVisibility);
	}
}

void UPlayerWidget::UpdateFPS(float NewFPS)
{
	if (FPSText)
	{
		FPSText->SetText(FText::AsNumber(NewFPS));
	}
}



