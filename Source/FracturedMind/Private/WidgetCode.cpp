// Fill out your copyright notice in the Description page of Project Settings.


#include "FracturedMind/Public/WidgetCode.h"

#include "Components/Button.h"
#include "FracturedMind/Public/Terminal.h"
#include "Components/EditableTextBox.h" 


void UWidgetCode::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (SubmitButton)
		SubmitButton->OnClicked.AddDynamic(this, &UWidgetCode::OnSubmitPassword);
	if (BackButton)
		BackButton->OnClicked.AddDynamic(this, &UWidgetCode::OnBackButtonClicked);

	//PasswordInput->SetFocus();
}

void UWidgetCode::OnSubmitPassword()
{
	if (PasswordInput)
	{
		EnteredPassword = PasswordInput->GetText().ToString();
		if (EnteredPassword.Len() > 0)
		{
			// UpdateMonitorScreen();
			
			if (OwningTerminal)
			{
				if (EnteredPassword.ToLower() == OwningTerminal->MonitorPassword.ToLower())
				{
					OwningTerminal->ActivateActivators();
					OwningTerminal->bIsInteractable = false;
					OwningTerminal->MonitorWidgetComponent->SetWidgetClass(OwningTerminal->AccessGrantedWidgetClass);
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, "Wrong");
				}
				OwningTerminal->CloseMonitorUI();
			}
		}
	}
}

void UWidgetCode::OnBackButtonClicked()
{
	OwningTerminal->CloseMonitorUI();
}
