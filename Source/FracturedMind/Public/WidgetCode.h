// Fill out your copyright notice in the Description page of Project Settings.#pragma once
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h" 

#include "WidgetCode.generated.h"

class UTextBlock;
class UEditableTextBox;
class UButton;
class ATerminal;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseAnimationFinished);
UCLASS()
class FRACTUREDMIND_API UWidgetCode : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Puzzle")
	FString EnteredPassword;
	
	UPROPERTY(BlueprintReadWrite, Category = "Monitor")
	ATerminal* OwningTerminal;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnCloseAnimationFinished OnCloseAnimationFinished;
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* PasswordInput;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ErrorText;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SubmitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OpeningTerminalUI;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ClosingTerminalUI;
	
	UFUNCTION()
	void OnSubmitPassword();

	UFUNCTION()
	void OnBackButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void PlayCloseAnimation();
	
};
