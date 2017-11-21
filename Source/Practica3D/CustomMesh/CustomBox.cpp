// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomBox.h"


// Sets default values
ACustomBox::ACustomBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	P_mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Generated mesh"));
	RootComponent = P_mesh;
	P_mesh->bUseAsyncCooking = true;
	MeshSection = 0;
	Size = 100.f;
}

// Called when the game starts or when spawned
void ACustomBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomBox::PostActorCreated()
{
	Super::PostActorCreated();
	CreateBox(Size);
}

void ACustomBox::PostLoad()
{
	Super::PostLoad();
	CreateBox(Size);
}

void ACustomBox::CreateTriangle(float Length, float Loc, float Depth, bool bInverted, ECustomAxis Axis)
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

void ACustomBox::CreatePlane(float Width, float Height, float Depth, bool bInverted, ECustomAxis Axis)
{
	const float TriangleWidth = Width / 2;
	const float TriangleHeigth = Height / 2;
	const float NewDepth = Depth / 2;
	
	CreateTriangle(TriangleWidth, -TriangleWidth, NewDepth, bInverted, Axis);
	CreateTriangle(TriangleWidth, TriangleWidth, NewDepth, bInverted, Axis);
}

void ACustomBox::CreateBox(float Width)
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
