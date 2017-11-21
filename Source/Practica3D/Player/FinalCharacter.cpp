// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalCharacter.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "CustomMesh/TheTriangle.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AFinalCharacter::AFinalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFinalCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawLine();
	CheckForCollision();
}

// Called to bind functionality to input
void AFinalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFinalCharacter::DrawLine()
{
	// This is just for cosmetic purposes, not doing any work.
	FHitResult Hit;
	FCollisionQueryParams FCQP;
	FCQP.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 300.f, ECollisionChannel::ECC_Camera, FCQP);
	if (Hit.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), Hit.Location, FColor::Blue, false, 0.06f, 2.f, 4.f);

		ATheTriangle* HitTriangle = Cast<ATheTriangle>(Hit.GetActor());
		if (HitTriangle)
		{
			//UE_LOG(LogTemp, Warning, TEXT("We hit something"));
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 300.f, FColor::Blue, false, 0.06f, 2.f, 4.f);
	}
}

void AFinalCharacter::CheckForCollision()
{
	FVector MyLoc = GetActorLocation();
	FVector MyForward = GetActorForwardVector();

	TArray<AActor*> FoundTriangles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATheTriangle::StaticClass(), FoundTriangles);
	if (FoundTriangles.Num() == 0) return;
	
	bool InTriangle = false;
	ATheTriangle* Choosen = Cast<ATheTriangle>(FoundTriangles[0]);
	for (auto i = 0; i < 10; ++i)
	{
		FVector Point = MyLoc + MyForward * i * 10;
		bool Omy = Choosen->CheckCollision(Point);
		UE_LOG(LogTemp, Warning, TEXT("Point is inside?: %s"), Omy ? TEXT("true") : TEXT("false"));
		if (Omy)
		{
			InTriangle = true;
			break;
		}
	}
	if (InTriangle)
	{
		Choosen->ApplyMat(true);
	}
	else
	{
		Choosen->ApplyMat(false);
	}
}