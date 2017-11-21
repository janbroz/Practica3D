// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheTriangle.generated.h"

UCLASS()
class PRACTICA3D_API ATheTriangle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheTriangle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create the triangle
	void CreateTriangle();

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;

	bool CheckCollision(FVector Point);

	void ApplyMat(bool Inside);

	UPROPERTY(VisibleAnywhere)
		FVector pointa;
	UPROPERTY(VisibleAnywhere)
		FVector pointb;
	UPROPERTY(VisibleAnywhere)
		FVector pointc;

public:
	UPROPERTY(VisibleAnywhere)
		class UProceduralMeshComponent* P_mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
		UMaterial* NormalTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
		UMaterial* LaserTexture;
};
