// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class USettingsWidget;
class UButton;
/**
 * 
 */
UCLASS()
class UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ReturnToMainMenuButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Pause Menu | UI")
	TSubclassOf<UUserWidget> SettingsWidgetClass;
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Resume();

	UFUNCTION()
	void OpenSettings();

	UFUNCTION()
	void ReturnToMainMenu();

	UFUNCTION()
	void Quit();
private:
	UUserWidget* SettingsWidget;
};
