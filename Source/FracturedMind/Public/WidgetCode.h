// Fill out your copyright notice in the Description page of Project Settings.#pragma once
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h" 

#include "WidgetCode.generated.h"

class UTextBlock;
class UEditableTextBox;
class UButton;
class ATerminal;

UCLASS()
class FRACTUREDMIND_API UWidgetCode : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Puzzle")
	FString EnteredPassword;
	
	UPROPERTY(BlueprintReadWrite, Category = "Monitor")
	ATerminal* OwningTerminal;
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
	
	UFUNCTION()
	void OnSubmitPassword();

	UFUNCTION()
	void OnBackButtonClicked();
	
};
