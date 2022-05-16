// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetDummy.generated.h"

UCLASS()
class LEARNUE4_API ATargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, class UAttributeComponent* OwningComp, float NewHealth, float Delta);

public:	


};
