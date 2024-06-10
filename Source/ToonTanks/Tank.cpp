// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    TankPlayerController = Cast<APlayerController>(GetController());
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward") , this , &ATank::Move); //this is getting called for every frame
    PlayerInputComponent->BindAxis(TEXT("Turn") , this , &ATank::Turn); //this is getting called for every frame

    PlayerInputComponent->BindAction(TEXT("Fire") , IE_Pressed , this , &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController)
    {   
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility , false , HitResult);

        // DrawDebugSphere(
        //     GetWorld(),
        //     HitResult.ImpactPoint,
        //     25.f,
        //     12,
        //     FColor::Red,
        //     false,
        //     -1.f
        // );

        RotateTurrent(HitResult.ImpactPoint);
    }

}


void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
    //The Movement we are achiveing here is improper , i.e it is frame dependent instead of timedependent , so we need to make it 
    //time dependent , using deltaTime concept  
    // = value * speed * deltaTime
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation,true);

}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;

    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation , true);

}


void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}