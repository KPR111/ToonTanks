// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Mesh"));
	TurrentMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurrentMesh);

}

// Called when the game starts or when spawned


void ABasePawn::RotateTurrent(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurrentMesh->GetComponentLocation();
	// FRotator LookAtRotation = ToTarget.Rotation();
	// we don't required entire turrent to rotate in pitch , yaw and other component , we only need it to rotate in yaw component
	FRotator LookAtRotation = FRotator(0.f , ToTarget.Rotation().Yaw , 0.f);
	// TurrentMesh->SetWorldRotation(LookAtRotation);
	// the above one is not good it is very fast when we put the pointer on the tank
	TurrentMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurrentMesh->GetComponentRotation(),
			 LookAtRotation,
			 UGameplayStatics::GetWorldDeltaSeconds(this)
			 ,5.f 
		)
	);
}



void ABasePawn::Fire()
{	
    FVector  Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,Location , Rotation);
	Projectile->SetOwner(this);
	// DrawDebugSphere(
	// 	GetWorld(),
	// 	Location,
	// 	25.f,
	// 	12.f,
	// 	FColor::Red,
	// 	false,
	// 	3.f
	// );


}


void ABasePawn::HandleDestruction()
{
	//Visual as well as Sound Effects need to be added here 
}
