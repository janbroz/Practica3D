// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Player/PracticaPlayerController.h"
#include "Math/Matrix.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	P_mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Generated mesh"));
	P_mesh->SetupAttachment(RootComponent);
	//RootComponent = P_mesh;
	P_mesh->bUseAsyncCooking = true;
	Size = 100.f;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap );
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::AddMovement(float Amount, ECustomAxis Axis)
{
	FMatrix Mat = FMatrix(FVector(1,0,0), FVector(0,1,0), FVector(0,0,1), FVector(0,0, 0));
	if (Axis == ECustomAxis::X_Axis)
	{
		Mat.M[1][3] = -Amount * 2.f;
	}
	else
	{
		Mat.M[0][3] = -Amount * 2.f;
	}

	FVector MyPos = GetActorLocation();
	FVector NewLoc = MTimes(Mat, MyPos);

	SetActorLocation(NewLoc);
	//UE_LOG(LogTemp, Warning, TEXT("Matrix mult is: %s"), *NewLoc.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("The matrix is: %s"), *Mat.ToString() );
	//UE_LOG(LogTemp, Warning, TEXT("The matrix at 1- 3 is: %f"), Mat.M[1][3]);
	
}

void APlayerCharacter::PostActorCreated()
{
	Super::PostActorCreated();
	CreateBox(Size);
}

void APlayerCharacter::PostLoad()
{
	Super::PostLoad();
	CreateBox(Size);
}

void APlayerCharacter::CreateTriangle(float Length, float Loc, float Depth, bool bInverted, ECustomAxis Axis)
{
	TArray<FVector> vertices;
	if (Axis == ECustomAxis::Z_Axis)
	{
		vertices.Add(FVector(Depth, Loc, Loc).RotateAngleAxis(90, FVector(0, 0, 1)));
		vertices.Add(FVector(Depth, Loc, -Loc).RotateAngleAxis(90, FVector(0, 0, 1)));
		vertices.Add(FVector(Depth, -Loc, Loc).RotateAngleAxis(90, FVector(0, 0, 1)));
	}
	else if (Axis == ECustomAxis::Y_Axis)
	{
		vertices.Add(FVector(Depth, Loc, Loc).RotateAngleAxis(90, FVector(0, 1, 0)));
		vertices.Add(FVector(Depth, Loc, -Loc).RotateAngleAxis(90, FVector(0, 1, 0)));
		vertices.Add(FVector(Depth, -Loc, Loc).RotateAngleAxis(90, FVector(0, 1, 0)));
	}
	else
	{
		vertices.Add(FVector(Depth, Loc, Loc));
		vertices.Add(FVector(Depth, Loc, -Loc));
		vertices.Add(FVector(Depth, -Loc, Loc));
	}

	TArray<int32> Triangles;
	if (bInverted)
	{
		Triangles.Add(0);
		Triangles.Add(1);
		Triangles.Add(2);
	}
	else
	{
		Triangles.Add(0);
		Triangles.Add(2);
		Triangles.Add(1);
	}

	TArray<FVector> normals;
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));


	TArray<FProcMeshTangent> tangents;
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));

	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

	P_mesh->CreateMeshSection_LinearColor(MeshSection, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
	MeshSection++;
	P_mesh->ContainsPhysicsTriMeshData(true);
}

void APlayerCharacter::CreatePlane(float Width, float Height, float Depth, bool bInverted, ECustomAxis Axis)
{
	const float TriangleWidth = Width / 2;
	const float TriangleHeigth = Height / 2;
	const float NewDepth = Depth / 2;

	CreateTriangle(TriangleWidth, -TriangleWidth, NewDepth, bInverted, Axis);
	CreateTriangle(TriangleWidth, TriangleWidth, NewDepth, bInverted, Axis);
}

void APlayerCharacter::CreateBox(float Width)
{
	// Create front and back plane.
	CreatePlane(Width, Width, -Width, false, ECustomAxis::X_Axis);
	CreatePlane(Width, Width, Width, true, ECustomAxis::X_Axis);

	// Create Left and right plane.
	CreatePlane(Width, Width, -Width, false, ECustomAxis::Y_Axis);
	CreatePlane(Width, Width, Width, true, ECustomAxis::Y_Axis);

	// Create top and down plane.
	CreatePlane(Width, Width, -Width, false, ECustomAxis::Z_Axis);
	CreatePlane(Width, Width, Width, true, ECustomAxis::Z_Axis);
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACustomBox* TheBox = Cast<ACustomBox>(OtherActor);
	APracticaPlayerController* Pc = Cast<APracticaPlayerController>(GetController());
	if (!TheBox || !Pc) return;
	
	Pc->ModifyLives(-1);
	TheBox->KillItWithFire();
	UE_LOG(LogTemp, Warning, TEXT("Ouch, we collided"));

}


FVector APlayerCharacter::MTimes(FMatrix M, FVector V)
{
	FVector4 NewVector = FVector4(0,0,0,0);
	FVector4 NV = FVector4(V[0], V[1], V[2], 1);
	UE_LOG(LogTemp, Warning, TEXT("Vector at is: %f"), NewVector[3]);
	for (int i = 0; i < 4; i++) {
		float acum = 0;
		for (int j = 0; j < 4; j++) {
			acum += M.M[i][j]* NV[j];
		}
		NewVector[i] = acum;
	}
	float w = NewVector[3];
	if (w != 1) {
		for (int i = 0; i < 4; i++) {
			NewVector[i] = NewVector[i] / w;
		}
	}

	return FVector(NewVector[0], NewVector[1], NewVector[2]);
}