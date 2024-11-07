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
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(Config)
	float Volume;

	UPROPERTY(Config)
	float Sensitivity;

	UPROPERTY(Config)
	bool bIsFPSShown;
	
	UFUNCTION()
	static UPlayerGameUserSettings* GetPlayerGameUserSettings();

	FString GetResolution() const;
};
