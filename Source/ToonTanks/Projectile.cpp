// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"
// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent->MaxSpeed = 1300.f;

	SmokeTrial = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrial->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this, LunchSound, GetActorLocation());
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		return;
	}
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, UDamageType::StaticClass());
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	Destroy();
}
