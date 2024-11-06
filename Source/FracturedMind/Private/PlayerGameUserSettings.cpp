// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameUserSettings.h"


void UPlayerGameUserSettings::SetMasterVolume(float Volume)
{
	MasterVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
	SaveConfig();
}

float UPlayerGameUserSettings::GetMasterVolume() const
{
	return MasterVolume;
}

void UPlayerGameUserSettings::SetMouseSensitivity(float Sensitivity)
{
	MouseSensitivity = FMath::Clamp(Sensitivity, 0.1f, 10.0f);
	SaveConfig();
}

float UPlayerGameUserSettings::GetMouseSensitivity() const
{
	return MouseSensitivity;
}
