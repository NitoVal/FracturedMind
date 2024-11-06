// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "PlayerGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class UPlayerGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config)
	float MasterVolume = 1.0f;

	UPROPERTY(Config)
	float MouseSensitivity = 1.0f;

	void SetMasterVolume(float Volume);
	float GetMasterVolume() const;

	void SetMouseSensitivity(float Sensitivity);
	float GetMouseSensitivity() const;
};
