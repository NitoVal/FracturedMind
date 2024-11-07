// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

class UTextBlock;
class UComboBoxString;
class USlider;
class UComboBoxKey;
class UCheckBox;
class UButton;
/**
 * 
 */
UCLASS()
class USettingsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ResolutionsComboBox;
	
	UPROPERTY(meta = (BindWidget))
	USlider* VolumeSlider;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* VolumeText;
	
	UPROPERTY(meta = (BindWidget))
	USlider* SensitivitySlider;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SensitivityText;
	
	UPROPERTY(meta = (BindWidget))
	UCheckBox* ShowFPSCheckBox;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ApplyButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings Menu | Audio")
	USoundMix* MasterMixAudio;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings Menu | Audio")
	USoundClass* MasterAudio;
	
	UPROPERTY()
	TArray<FIntPoint> Resolutions;
	
	UFUNCTION()
	void OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	UFUNCTION()
	void SetVolume(float Volume);

	UFUNCTION()
	void SetSensitivity(float Value);
	
	UFUNCTION()
	void SetShowFPS(bool State);
	
	UFUNCTION()
	void ApplySettings();
	
	UFUNCTION()
	void Back();
	
	void OnSettingsModified();
	void UpdateApplyButtonState();
private:
	bool bAreSettingsChanged;
	bool bIsShowFPSOn;
	float CurrentVolume;
	float CurrentSensitivity;
	FIntPoint SelectedResolution;
};
