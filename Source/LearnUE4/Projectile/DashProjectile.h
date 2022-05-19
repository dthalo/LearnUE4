// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "DashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API ADashProjectile : public AProjectileBase
{
	GENERATED_BODY()
public:
	ADashProjectile();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
		float TeleportDelay;
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
		float DetonateDelay;

	FTimerHandle TimerHandle_DelayDetonate;

	virtual void Explode_Implementation() override;

	void TeleportInstigator();
	virtual void BeginPlay() override;

protected:
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
};
