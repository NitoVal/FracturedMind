// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetCode.h"

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
}

void UWidgetCode::OnCodeEntered(const FText& Text, ETextCommit::Type CommitMethod)
{
	// Vérifiez si l'utilisateur a appuyé sur "Entrée" pour valider son code
	if (CommitMethod == ETextCommit::OnEnter)
	{
		FString EnteredCode = Text.ToString();
        
		// Traitement du code saisi, par exemple, comparer avec un code attendu
		if (EnteredCode == "1234") // Exemple de code correct
		{
			AwaitingInputText->SetText(FText::FromString("Code Correct"));
			AwaitingInputText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
		}
		else
		{
			AwaitingInputText->SetText(FText::FromString("Code Incorrect"));
			AwaitingInputText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		}

		// Réinitialiser le champ de texte pour permettre une nouvelle entrée
		CodeInputBox->SetText(FText::GetEmpty());
	}
}
