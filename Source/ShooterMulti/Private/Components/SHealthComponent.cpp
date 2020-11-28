// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMulti/Public/Components/SHealthComponent.h"
#include "Net/UnrealNetwork.h" // contains DOREPLIFETIME MACRO

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//team default number for enemy team
	TeamNum = 255;

	// ...
	DefaultHealth = 100;


	SetIsReplicated(true);
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// only hook if we are on the server
	if (GetOwnerRole() == ROLE_Authority)
	{

		AActor* MyOwner = GetOwner();
		if (MyOwner)
		{
			MyOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::HandleTakeAnyDamage);
		}

	}
	Health = DefaultHealth;

}

void USHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{

	if (Damage <= 0.0f)
	{
		return;
	}

	if (DamagedActor != DamageCauser && IsFriendly(DamagedActor, DamageCauser))
	{
		return;
	}


	//update health clamped
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);


	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);

}


void USHealthComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USHealthComponent, Health);
}

bool USHealthComponent::IsFriendly(AActor* A, AActor* B)
{
	if (A == nullptr || B == nullptr)
	{
		//assume friendly
		return true;
	}


	USHealthComponent* HealthCompA = Cast<USHealthComponent>(A->GetComponentByClass(USHealthComponent::StaticClass() ) );
	USHealthComponent* HealthCompB = Cast<USHealthComponent>(B->GetComponentByClass(USHealthComponent::StaticClass()));

	if (HealthCompA == nullptr || HealthCompB == nullptr)
	{
		//assume friendly
		return true;
	}

	return HealthCompA->TeamNum == HealthCompB->TeamNum;

}