// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGMB.h"

AMainGMB::AMainGMB() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}