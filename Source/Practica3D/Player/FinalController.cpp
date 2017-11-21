// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalController.h"
#include "Player/FinalCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"


AFinalController::AFinalController()
{
	bShowMouseCursor = true;
}


void AFinalController::BeginPlay()
{
	Super::BeginPlay();

	ThePawn = Cast<AFinalCharacter>(GetPawn());
}

void AFinalController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("VerticalMov", this, &AFinalController::VerticalMov);
	InputComponent->BindAxis("LateralMov", this, &AFinalController::LateralMov);
}


void AFinalController::VerticalMov(float Amount)
{
	if (!ThePawn || Amount == 0.f)return;

	ThePawn->GetCharacterMovement()->AddInputVector(FVector::RightVector * Amount);
}

void AFinalController::LateralMov(float Amount)
{
	if (!ThePawn || Amount == 0.f)return;

	ThePawn->GetCharacterMovement()->AddInputVector(FVector::ForwardVector * Amount);
}