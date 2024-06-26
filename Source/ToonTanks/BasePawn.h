// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurrent(FVector LookAtTarget);
	void Fire();



private:
	UPROPERTY(VisibleAnyWhere , BlueprintReadOnly , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnyWhere , BlueprintReadOnly , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
                    
	UPROPERTY(VisibleAnyWhere , BlueprintReadOnly , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurrentMesh;

	UPROPERTY(VisibleAnyWhere , BlueprintReadOnly , Category = "Components" , meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly , Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;


};
