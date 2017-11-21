// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FinalController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICA3D_API AFinalController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFinalController();

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;


	void VerticalMov(float Amount);
	void LateralMov(float Amount);
	

public:
	class AFinalCharacter* ThePawn;
};
