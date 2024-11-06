// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

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
	// UPROPERTY(meta = (BindWidget))
	// UComboBoxKey* DisplayComboBox;
	
	// UPROPERTY(meta = (BindWidget))
	// UComboBoxKey* ResolutionsComboBox;

	// UPROPERTY(meta = (BindWidget))
	// UComboBoxKey* FramerateComboBox;
	
	UPROPERTY(meta = (BindWidget))
	UCheckBox* VSyncCheckBox;
	
	UPROPERTY(meta = (BindWidget))
	USlider* VolumeSlider;
	
	UPROPERTY(meta = (BindWidget))
	USlider* SensitivitySlider;
	
	UPROPERTY(meta = (BindWidget))
	UCheckBox* ShowFPSCheckBox;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ApplyButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetVSync(bool State);
	
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
private:
	bool bAreSettingsChanged;
};
