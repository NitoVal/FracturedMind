// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameUserSettings.h"

UPlayerGameUserSettings::UPlayerGameUserSettings(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer) //Constructor
{
	Volume = 1;
	Sensitivity = 1;
	bIsFPSShown = false;
}

UPlayerGameUserSettings* UPlayerGameUserSettings::GetPlayerGameUserSettings()
{
	return Cast<UPlayerGameUserSettings>(GetGameUserSettings());
}

FString UPlayerGameUserSettings::GetResolution() const
{
	const FIntPoint ResolutionPoint = GetScreenResolution();
	return FString::Printf(TEXT("%dx%d"), ResolutionPoint.X, ResolutionPoint.Y);
}
