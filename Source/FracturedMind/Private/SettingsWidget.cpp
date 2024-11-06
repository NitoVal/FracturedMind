// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"

#include "PlayerGameUserSettings.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "FracturedMind/PlayerCharacter.h"
#include "FracturedMind/PlayerWidget.h"
#include "Kismet/GameplayStatics.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UPlayerGameUserSettings* GameSettings = Cast<UPlayerGameUserSettings>(GEngine->GetGameUserSettings());
	if (!GameSettings)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to retrieve GameUserSettings"));
		return;
	}
	if (VolumeSlider)
	{
		VolumeSlider->OnValueChanged.AddDynamic(this, &USettingsWidget::SetVolume);
		VolumeSlider->SetValue(GameSettings->GetMasterVolume());
	}
	if (SensitivitySlider)
	{
		SensitivitySlider->OnValueChanged.AddDynamic(this, &USettingsWidget::SetSensitivity);
		SensitivitySlider->SetValue(GameSettings->GetMouseSensitivity());
	}
	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddDynamic(this, &USettingsWidget::ApplySettings);
		ApplyButton->SetIsEnabled(false);
	}
	if (BackButton)
		BackButton->OnClicked.AddDynamic(this, &USettingsWidget::Back);
}

void USettingsWidget::SetVSync(bool State)
{

}

void USettingsWidget::SetVolume(float Volume)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), nullptr, nullptr, Volume, 1.0f, 0.0f);
}

void USettingsWidget::SetSensitivity(float Sensitivity)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->SetSensitivity(Sensitivity);
}

void USettingsWidget::SetShowFPS(bool State)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->PlayerWidget->SetFPSCounterVisibility(State);
}

void USettingsWidget::ApplySettings()
{
	bAreSettingsChanged = false;
}

void USettingsWidget::Back()
{
	RemoveFromParent();
}

void USettingsWidget::OnSettingsModified()
{
	bAreSettingsChanged = true;
}
