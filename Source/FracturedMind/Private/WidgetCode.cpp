// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetCode.h"

#include "Terminal.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h" 
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h" 

void UWidgetCode::NativeConstruct()
{
	Super::NativeConstruct();
 
	if (AwaitingInputText)
	{
		AwaitingInputText->SetText(FText::FromString("Awaiting Input..."));
		AwaitingInputText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
	}

	if (CodeInputBox)
	{   
		CodeInputBox->OnTextCommitted.AddDynamic(this, &UWidgetCode::OnCodeEntered);
	}

	CorrectCode = false;
}

void UWidgetCode::OnCodeEntered(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		FString EnteredCode = Text.ToString();
        
		if (EnteredCode == "1234") 
		{
			CorrectCode = true; 
			AwaitingInputText->SetText(FText::FromString("Code Correct"));
			AwaitingInputText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
			this->SetVisibility(ESlateVisibility::Hidden);
			if (OwningTerminal)
			{
				OwningTerminal->CheckCode();
			} 
		}
		else
		{
			CorrectCode = false; 
			AwaitingInputText->SetText(FText::FromString("Code Incorrect"));
			AwaitingInputText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
			this->SetVisibility(ESlateVisibility::Hidden);
			if (OwningTerminal)
			{
				OwningTerminal->CheckCode();
			}
		}
		CodeInputBox->SetText(FText::GetEmpty());
	}
}
