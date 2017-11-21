// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomMesh/CustomBox.h"
#include "PracticaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICA3D_API APracticaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APracticaPlayerController();
	
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	class APlayerCharacter* Pc;

	void VerticalMov(float Amount);
	void LateralMov(float Amount);
	void ActionBar();
	void ModifyLives(int32 Amount);

private:
	const int32 MAX_LIVES = 5;
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerScore")
		int32 Score;	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerScore")
		int32 Lives;

};
