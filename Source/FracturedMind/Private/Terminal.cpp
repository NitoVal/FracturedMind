#include "Terminal.h"
#include "WidgetCode.h"
#include "Blueprint/UserWidget.h"
#include "FracturedMind/Door.h"
#include "FracturedMind/PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ATerminal::ATerminal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	TerminalMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMeshComponent"));
	TerminalMeshComponent->SetupAttachment(RootComponent);

	ClavierMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClavierMeshComponent"));
	ClavierMeshComponent->SetupAttachment(RootComponent);

	ScreenMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScreenMeshComponent"));
	ScreenMeshComponent->SetupAttachment(RootComponent);

	Code = {1, 2, 3, 4};
	CurrentCodeInput = {};
}

// Called when the game starts or when spawned
void ATerminal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATerminal::Interact()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(FInputModeUIOnly());
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetCodeClass);
	WidgetCode = Cast<UWidgetCode>(WidgetCode);
	WidgetCode->AddToViewport();
}

bool ATerminal::IsInteractable()
{
	return true;
}

void ATerminal::EnterCode(int32 CodeDigit)
{
	CurrentCodeInput.Add(CodeDigit);

	if (CurrentCodeInput.Num() == Code.Num())
	{
		CheckCode();
	}
}

void ATerminal::CheckCode()
{
	if (CurrentCodeInput == Code && LinkedDoor)
	{
		LinkedDoor->OpenDoor();
	}
	else
	{
		CurrentCodeInput.Empty();
	}
}