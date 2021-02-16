// Fill out your copyright notice in the Description page of Project Settings.

#include "SCritter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASCritter::ASCritter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(-300.0f, 0.0f, 300.f));
	Camera->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));



	CurrentVelocity = FVector(0.f);

	MaxSpeed = 100.f;

}

// Called when the game starts or when spawned
void ASCritter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCritter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void ASCritter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASCritter::MoveForward(float Value)
{
	//AddMovementInput(GetActorForwardVector() * Value);

	// OR

	CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;

}

void ASCritter::MoveRight(float Value)
{
	//AddMovementInput(GetActorRightVector() * Value);
	CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;

}

