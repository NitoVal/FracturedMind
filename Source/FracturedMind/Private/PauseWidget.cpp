// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"

#include "SettingsWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "FracturedMind/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ResumeButton)
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::Resume);
	if (SettingsButton)
		SettingsButton->OnClicked.AddDynamic(this, &UPauseWidget::OpenSettings);
	if (ReturnToMainMenuButton)
		ReturnToMainMenuButton->OnClicked.AddDynamic(this, &UPauseWidget::ReturnToMainMenu);
	if (QuitButton)
		QuitButton->OnClicked.AddDynamic(this, &UPauseWidget::Quit);
}

void UPauseWidget::SetVisibility(ESlateVisibility InVisibility)
{
	// Skip animations if not enabled
	if (!bShouldPlayAnimations)
	{
		Super::SetVisibility(InVisibility);
		return;
	}

	if (InVisibility == ESlateVisibility::Visible)
	{
		Super::SetVisibility(InVisibility);

		if (OpeningPauseAnimation)
			PlayAnimation(OpeningPauseAnimation);
	}
	else if (InVisibility == ESlateVisibility::Hidden || InVisibility == ESlateVisibility::Collapsed)
	{
		if (ClosingPauseAnimation)
		{
			PlayAnimation(ClosingPauseAnimation);

			FTimerHandle TimerHandle;
			float AnimationDuration = ClosingPauseAnimation->GetEndTime();

			if (AnimationDuration > 0.f)
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, InVisibility](){ Super::SetVisibility(InVisibility); }, AnimationDuration, false);
			else
				Super::SetVisibility(InVisibility);
		}
		else
			Super::SetVisibility(InVisibility);
	}
}

void UPauseWidget::SetShouldPlayAnimations(bool bShouldPlay)
{
	bShouldPlayAnimations = bShouldPlay;
}

void UPauseWidget::Resume()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->Pause();
}

void UPauseWidget::OpenSettings()
{
	if (SettingsWidgetClass)
	{
		UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), SettingsWidgetClass);
		SettingsWidget = UserWidget;
		SettingsWidget->AddToViewport();
	}
}

void UPauseWidget::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenuLevel"));
}

void UPauseWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
