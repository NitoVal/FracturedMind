// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Bind functions to button clicks
	if (NewGameButton)
		NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameClicked);
	if (SettingsButton)
		SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClicked);
	if (QuitButton)
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
}

void UMainMenuWidget::OnNewGameClicked()
{
	UGameplayStatics::OpenLevel(this, FName("LabMap"));
}

void UMainMenuWidget::OnSettingsClicked()
{
	// Open settings menu or widget
}

void UMainMenuWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
