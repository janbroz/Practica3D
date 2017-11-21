// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProceduralMeshComponent.h"
#include "CustomMesh/CustomBox.h"
#include "PlayerCharacter.generated.h"




UCLASS()
class PRACTICA3D_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* P_mesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		uint32 bUpperPart : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Size;
	int32 MeshSection;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	void CreateTriangle(float Length, float Loc, float Depth, bool bInverted, ECustomAxis Axis);
	void CreatePlane(float Width, float Height, float Depth, bool bInverted, ECustomAxis Axis);
	void CreateBox(float Width);

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	void AddMovement(float Amount, ECustomAxis Axis);

	FVector MTimes(FMatrix M, FVector V);
	
};
