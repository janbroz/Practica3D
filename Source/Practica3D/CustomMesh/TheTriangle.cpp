// Fill out your copyright notice in the Description page of Project Settings.

#include "TheTriangle.h"
#include "ProceduralMeshComponent.h"

// Sets default values
ATheTriangle::ATheTriangle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	P_mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Generated mesh"));
	RootComponent = P_mesh;
	P_mesh->bUseAsyncCooking = true;
}

// Called when the game starts or when spawned
void ATheTriangle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATheTriangle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//UE_LOG(LogTemp, Warning, TEXT("the draw matrix: %s"), *P_mesh->GetRenderMatrix().ToString());
}

void ATheTriangle::CreateTriangle()
{
	TArray<FVector> vertices;

	vertices.Add(FVector(0, 0, 0));
	vertices.Add(FVector(-200, 0, 0));
	vertices.Add(FVector(0, 0, 200));
	
	TArray<int32> Triangles;
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

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

	

	P_mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
	P_mesh->ContainsPhysicsTriMeshData(true);

	P_mesh->SetMaterial(0, NormalTexture);

	pointa = GetActorLocation();
	pointb = FVector(-200, 0, 0);
	pointc = pointa + FVector(0, 0, 200);
}

void ATheTriangle::PostActorCreated()
{
	Super::PostActorCreated();
	CreateTriangle();
}

void ATheTriangle::PostLoad()
{
	Super::PostLoad();
	CreateTriangle();
}

bool ATheTriangle::CheckCollision(FVector Point)
{
	//UE_LOG(LogTemp, Warning, TEXT("Checking Point at: %s"), *Point.ToString());

	// Define the area of the triangles: 
	FVector v0 = pointb - pointa; //(b-a)
	FVector v1 = pointc - pointa; //(c-a)
	FVector v2 = Point - pointa; //(a-p0)
	
	float d00 = FVector::DotProduct(v0, v0); // Length of v0
	float d01 = FVector::DotProduct(v0, v1); // v0v1
	float d11 = FVector::DotProduct(v1, v1); // Length of v1
	float d20 = FVector::DotProduct(v2, v0); // v2v0
	float d21 = FVector::DotProduct(v2, v1); // v2v1
	float det = d00*d11 - d01*d01;

	float v = (d11 * d20 - d01 * d21) / det;
	float w = (d00 * d21 - d01 * d20) / det;
	
	// Check if our areas are positive and their sum is less than 1
	return v >= 0.f && w >= 0.f && v + w <= 1.f;
}

void ATheTriangle::ApplyMat(bool Inside)
{
	if (Inside)
	{
		P_mesh->SetMaterial(0, LaserTexture);
	}
	else
	{
		P_mesh->SetMaterial(0, NormalTexture);
	}
}