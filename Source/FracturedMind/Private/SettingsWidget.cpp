// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"

#include "PlayerGameUserSettings.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxKey.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "FracturedMind/PlayerCharacter.h"
#include "FracturedMind/PlayerWidget.h"
#include "Kismet/GameplayStatics.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	const UPlayerGameUserSettings* PlayerGameUserSettings = Cast<UPlayerGameUserSettings>(GEngine->GetGameUserSettings());
	if (!PlayerGameUserSettings)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red ,"Failed to find game user settings");
		return;
	}
	
	if (ResolutionsComboBox)
	{
		Resolutions.Reset();
		UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

		ResolutionsComboBox->ClearOptions();
		for (const auto& Resolution : Resolutions)
		{
			const auto ResolutionString = FString::Printf(TEXT("%dx%d"),Resolution.X,Resolution.Y);
			ResolutionsComboBox->AddOption(ResolutionString);
		}
		ResolutionsComboBox->OnSelectionChanged.AddDynamic(this, &USettingsWidget::OnResolutionChanged);
		
		ResolutionsComboBox->SetSelectedOption(PlayerGameUserSettings->GetResolution());
	}
	if (VolumeSlider)
	{
		VolumeSlider->OnValueChanged.AddDynamic(this, &USettingsWidget::SetVolume);
		VolumeSlider->SetValue(PlayerGameUserSettings->Volume);
	}
	if (SensitivitySlider)
	{
		SensitivitySlider->OnValueChanged.AddDynamic(this, &USettingsWidget::SetSensitivity);
		SensitivitySlider->SetValue(PlayerGameUserSettings->Sensitivity);
	}
	if (ShowFPSCheckBox)
	{
		ShowFPSCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::SetShowFPS);
		ShowFPSCheckBox->SetCheckedState(PlayerGameUserSettings->bIsFPSShown? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	}
	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddDynamic(this, &USettingsWidget::ApplySettings);
		ApplyButton->SetIsEnabled(false);
	}
	if (BackButton)
		BackButton->OnClicked.AddDynamic(this, &USettingsWidget::Back);
}
void USettingsWidget::OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	const auto SelectedRes = Resolutions[ResolutionsComboBox->GetSelectedIndex()];
	UPlayerGameUserSettings* PlayerGameUserSettings = Cast<UPlayerGameUserSettings>(GEngine->GetGameUserSettings());
	PlayerGameUserSettings->SetScreenResolution(SelectedRes);
	PlayerGameUserSettings->ApplySettings(false);
	OnSettingsModified();
}

void USettingsWidget::SetVolume(float Volume)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterMixAudio, MasterAudio, Volume, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterMixAudio);
	VolumeText->SetText(FText::AsNumber(VolumeSlider->GetValue() * 100));
	CurrentVolume = Volume;
	OnSettingsModified();
}

void USettingsWidget::SetSensitivity(float Sensitivity)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
		Player->SetSensitivity(Sensitivity);

	SensitivityText->SetText(FText::AsNumber(SensitivitySlider->GetValue()));
	CurrentSensitivity = Sensitivity;
	OnSettingsModified();
}

void USettingsWidget::SetShowFPS(bool State)
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, "It goes here");
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
		Player->PlayerWidget->SetFPSCounterVisibility(State);
		
	bIsShowFPSOn = State;
	OnSettingsModified();
}

void USettingsWidget::ApplySettings()
{
	UPlayerGameUserSettings* PlayerGameUserSettings = Cast<UPlayerGameUserSettings>(GEngine->GetGameUserSettings());
	if (PlayerGameUserSettings)
	{
		PlayerGameUserSettings->Volume = CurrentVolume;
		PlayerGameUserSettings->Sensitivity = CurrentSensitivity;
		PlayerGameUserSettings->bIsFPSShown = bIsShowFPSOn;
	}
	bAreSettingsChanged = false;
	UpdateApplyButtonState();
}

void USettingsWidget::Back()
{
	RemoveFromParent();
}

void USettingsWidget::OnSettingsModified()
{
	bAreSettingsChanged = true;
	UpdateApplyButtonState();
}

void USettingsWidget::UpdateApplyButtonState()
{
	if (ApplyButton)
		ApplyButton->SetIsEnabled(bAreSettingsChanged);
}
