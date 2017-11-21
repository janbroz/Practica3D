// Fill out your copyright notice in the Description page of Project Settings.

#include "PracticaPlayerController.h"
#include "Player/PlayerCharacter.h"



APracticaPlayerController::APracticaPlayerController()
{
	bShowMouseCursor = true;
	Score = 0;
	Lives = 3;
}

void APracticaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("LateralMov", this, &APracticaPlayerController::LateralMov);
	InputComponent->BindAxis("VerticalMov", this, &APracticaPlayerController::VerticalMov);
	InputComponent->BindAction("Spacebar", IE_Pressed, this, &APracticaPlayerController::ActionBar);

}

void APracticaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Pc = Cast<APlayerCharacter>(GetPawn());

}

void APracticaPlayerController::ActionBar()
{
	UE_LOG(LogTemp, Warning, TEXT("Holi, action"));
		//UE_LOG(LogTemp, Warning, TEXT("Holi, vertical"));
	//Pc->AddMovement(10);
}

void APracticaPlayerController::VerticalMov(float Amount)
{
	if (!Pc) return;
	if (Amount != 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Holi, vertical"));
		//Pc->AddMovementInput(Pc->GetActorRightVector(), Amount);
		Pc->AddMovement(Amount, ECustomAxis::X_Axis);
	}
}

void APracticaPlayerController::LateralMov(float Amount)
{
	if (!Pc) return;
	if (Amount != 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Holi, lateral"));
		//Pc->AddMovementInput(Pc->GetActorForwardVector(), Amount);
		Pc->AddMovement(Amount, ECustomAxis::Y_Axis);
	}
}

void APracticaPlayerController::ModifyLives(int32 Amount)
{
	Lives = FMath::Clamp(Lives + Amount, 0, MAX_LIVES);
	if (Lives <= 0 )
	{
		RestartLevel();
	}
}