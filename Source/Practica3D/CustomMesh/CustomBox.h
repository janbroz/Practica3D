// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "CustomBox.generated.h"

UENUM(BlueprintType)
enum class ECustomAxis : uint8
{
	X_Axis,
	Y_Axis,
	Z_Axis
};

UCLASS()
class PRACTICA3D_API ACustomBox : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* P_mesh;
	int32 MeshSection;

public:	
	// Sets default values for this actor's properties
	ACustomBox();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		uint32 bUpperPart : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Size;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	void CreateTriangle(float Length, float Loc, float Depth, bool bInverted, ECustomAxis Axis);
	void CreatePlane(float Width, float Height, float Depth, bool bInverted, ECustomAxis Axis);
	void CreateBox(float Width);

	UFUNCTION(BlueprintImplementableEvent)
		void KillItWithFire();
	
};
