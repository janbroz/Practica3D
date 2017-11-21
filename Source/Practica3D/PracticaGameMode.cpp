// Fill out your copyright notice in the Description page of Project Settings.

#include "PracticaGameMode.h"
#include "Player/PracticaPlayerController.h"
#include "Player/PlayerCharacter.h"
#include "Player/FinalCharacter.h"
#include "Player/FinalController.h"


APracticaGameMode::APracticaGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PlayerControllerClass = APracticaPlayerController::StaticClass();
	//DefaultPawnClass = APlayerCharacter::StaticClass();

	PlayerControllerClass = AFinalController::StaticClass();
	DefaultPawnClass = AFinalCharacter::StaticClass();

}