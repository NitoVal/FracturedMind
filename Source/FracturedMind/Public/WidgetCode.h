// Fill out your copyright notice in the Description page of Project Settings.#pragma once
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h" 
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h" 
#include "WidgetCode.generated.h"

class ATerminal;

UCLASS()
class FRACTUREDMIND_API UWidgetCode : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, Category = "Code")
	bool CorrectCode;

	// Getter pour CorrectCode
	UFUNCTION(BlueprintCallable, Category = "Code")
	bool GetCorrectCode() const { return CorrectCode; }

	UPROPERTY()
	ATerminal* OwningTerminal;

	void SetOwningTerminal(ATerminal* Terminal) { OwningTerminal = Terminal; }

protected:
	 
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel; 
	
	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundImage;
 
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AwaitingInputText;
 
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CodeInputBox;

	UFUNCTION()
	void OnCodeEntered(const FText& Text, ETextCommit::Type CommitMethod); 
	
};
