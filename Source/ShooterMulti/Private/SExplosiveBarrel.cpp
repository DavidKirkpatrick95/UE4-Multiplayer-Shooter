// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "ShooterMulti/Public/Components/SHealthComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h" // contains DOREPLIFETIME MACRO


// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));
	HealthComp->OnHealthChanged.AddDynamic(this, &ASExplosiveBarrel::OnHealthChanged);

	bExploded = false;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MEshComp"));
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	RootComponent = MeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(MeshComp);
	RadialForceComp->Radius = 250;
	RadialForceComp->ImpulseStrength = 3527.74f;
	RadialForceComp->ForceStrength = 400;
	RadialForceComp->bIgnoreOwningActor = true;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->bAutoActivate = false;

	ExplosionImpulse = 400;

	SetReplicates(true);
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}
/*

void ASExplosiveBarrel::Explode()
{




}
*/

void ASExplosiveBarrel::OnHealthChanged(USHealthComponent* HealthCompParameter, float Health, float HealthDelta, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (bExploded)
	{
		return;
	}

	if (Health <= 0.0f)
	{
		//explode!


		//Explode();
		bExploded = true;
		OnRep_Exploded();



			FVector BoostIntensity = FVector::UpVector * ExplosionImpulse;
			MeshComp->AddImpulse(BoostIntensity, NAME_None, true);
			RadialForceComp->FireImpulse();


	}
	



}
/*
void ASExplosiveBarrel::ServerExplode_Implementation() {

	//play logic

	Explode();

}

bool ASExplosiveBarrel::ServerExplode_Validate() {



	return true;
}
*/
void ASExplosiveBarrel::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASExplosiveBarrel, bExploded);


	

}

void ASExplosiveBarrel::OnRep_Exploded()
{
	//the visual effects


	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	MeshComp->SetMaterial(0, ExplodedMaterial);



}