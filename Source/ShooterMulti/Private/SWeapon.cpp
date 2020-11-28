// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "ShooterMulti/ShooterMulti.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h" // contains DOREPLIFETIME MACRO

// Sets default values
ASWeapon::ASWeapon()
{

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";
	TracerTargetName = "Target";
	BaseDamage = 20.0f;
	RateOfFire = 600;

	SetReplicates(true);

	NetUpdateFrequency = 66.0f;
	MinNetUpdateFrequency = 33.0f;

	BulletSpread = 1.0f; //default bullet spread

}
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenShots = 60 / RateOfFire;
}


void ASWeapon::Fire()
{

	if (GetLocalRole() < ROLE_Authority)
	{
		//called if we are a client
		ServerFire();
	}


	AActor* MyOwner = GetOwner();


	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);


		FVector ShotDirection = EyeRotation.Vector();

		//make bullet spread
		float HalfRad = FMath::DegreesToRadians(BulletSpread);

		ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);


		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = true;

		//particle target param
		FVector TracerEndPoint = TraceEnd;

		EPhysicalSurface SurfaceType = SurfaceType_Default;


		//Trace world from pawn eyes to crosshair location
		FHitResult Hit;//struct to be filled with useful hit info
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, COLLISION_WEAPON, QueryParams))
		{

			//Blocking hit, Process Damage
			AActor* HitActor = Hit.GetActor();

			//get surface type
			SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());

			float ActualDamage = BaseDamage;
			if (SurfaceType == SURFACE_FLESHVULNERABLE)
			{
				ActualDamage *= 4.0f;
			}
			UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), MyOwner, DamageType);

			PlayImpactEffects(SurfaceType, Hit.ImpactPoint);


			TracerEndPoint = Hit.ImpactPoint;
		}

		//DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);
		PlayFireEffects(TracerEndPoint);

		if (GetLocalRole() == ROLE_Authority)
		{

				HitScanTrace.TraceTo = TracerEndPoint;

		}


		LastFireTime = GetWorld()->TimeSeconds;



	}
}

void ASWeapon::PlayFireEffects(FVector TracerEndPoint) {

	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}
	if (TracerEffect)
	{
		MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

		UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);

		if (TracerComp)
		{
			TracerComp->SetVectorParameter(TracerTargetName, TracerEndPoint);
		}
	}

	APawn* myOwner = Cast<APawn>(GetOwner() );
	if (myOwner)
	{
		APlayerController* PC = Cast<APlayerController>(myOwner->GetController() );
		if (PC)
		{
			PC->ClientPlayCameraShake(FireCamShake);
		}
	}

}


void ASWeapon::StartFire()
{
	float FirstDelay =FMath::Max (LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds , 0.0f);
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots,this,&ASWeapon::Fire,TimeBetweenShots,true, FirstDelay);

}

void ASWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);


}

//_Implementation required

void ASWeapon::ServerFire_Implementation()
{


	Fire();
	return;
}



bool ASWeapon::ServerFire_Validate()
{

	return true;
}

void ASWeapon::OnRep_HitScanTrace()
{

	//play cosmetics
	PlayFireEffects(HitScanTrace.TraceTo);

	PlayImpactEffects(HitScanTrace.SurfaceType, HitScanTrace.TraceTo);
}

void ASWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASWeapon, HitScanTrace,COND_SkipOwner);
}

void ASWeapon::PlayImpactEffects(EPhysicalSurface SurfaceType, FVector ImpactPoint)
{

	UParticleSystem* SelectedEffect = nullptr;

	switch (SurfaceType)
	{
	case SURFACE_FLESHDEFAULT: // flesh default
	case SURFACE_FLESHVULNERABLE:
		SelectedEffect = FleshImpactEffect;
		break;
	default:
		SelectedEffect = DefaultImpactEffect;
	}
	if (SelectedEffect)
	{
		FVector MuzzleLocation1 = MeshComp->GetSocketLocation(MuzzleSocketName);
		FVector ShotDirection = ImpactPoint - MuzzleLocation1;
		ShotDirection.Normalize();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, ImpactPoint, ShotDirection.Rotation());
	}



}