// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class LEARNUE4_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BlackHoleProjectileClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* AttackMontage;

	FTimerHandle TimerHandle_PrimaryAttack;

	FTimerHandle TimerHandle_BlackHoleAttack;

	FTimerHandle TimerHandle_Dash;

	UPROPERTY(EditDefaultsOnly)
	float AttackAnimDelay = 0.2f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	class UInterActionComponent* InterActionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UAttributeComponent* AttributeComp;

	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	virtual void PrimaryAttack();
	virtual void PrimaryInteract();

	virtual void PrimaryAttack_TimeElapsed();

	virtual void BlackHoleAttack();
	virtual void BlackHoleAttack_TimeElapsed();

	virtual void Dash();
	virtual void Dash_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
