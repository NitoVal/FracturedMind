// Fill out your copyright notice in the Description page of Project Settings.


#include "FracturedMind/Public/WidgetCode.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "FracturedMind/Public/Terminal.h"
#include "Components/EditableTextBox.h" 
#include "Components/TextBlock.h"


void UWidgetCode::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (OpeningTerminalUI)
		PlayAnimation(OpeningTerminalUI);
	
	if (SubmitButton)
		SubmitButton->OnClicked.AddDynamic(this, &UWidgetCode::OnSubmitPassword);
	if (BackButton)
		BackButton->OnClicked.AddDynamic(this, &UWidgetCode::OnBackButtonClicked);
}

void UWidgetCode::OnSubmitPassword()
{
	if (PasswordInput)
	{
		EnteredPassword = PasswordInput->GetText().ToString();
		if (EnteredPassword.Len() > 0)
		{
			if (OwningTerminal)
			{
				if (EnteredPassword.ToLower() == OwningTerminal->MonitorPassword.ToLower())
				{
					OwningTerminal->ActivateActivators();
					OwningTerminal->bIsInteractable = false;
					OwningTerminal->MonitorWidgetComponent->SetWidgetClass(OwningTerminal->AccessGrantedWidgetClass);
					PlayCloseAnimation();
				}
				else
				{
					ErrorText->SetText(FText::FromString("Incorrect Password"));
					PasswordInput->SetText(FText::FromString(""));
				}
			}
		}
	}
}

void UWidgetCode::OnBackButtonClicked()
{
	PlayCloseAnimation();
}

void UWidgetCode::PlayCloseAnimation()
{
	if (ClosingTerminalUI)
	{
		PlayAnimation(ClosingTerminalUI);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,[this](){ OnCloseAnimationFinished.Broadcast(); OwningTerminal->CloseMonitorUI();},ClosingTerminalUI->GetEndTime(),false);
	}
}
