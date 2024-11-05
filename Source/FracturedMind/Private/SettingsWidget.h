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
	
private:
};
