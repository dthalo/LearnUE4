// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "../Components/AttributeComponent.h"


// Sets default values
ATargetDummy::ATargetDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &ATargetDummy::OnHealthChanged);
}

// Called when the game starts or when spawned
void ATargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATargetDummy::OnHealthChanged(AActor* InstigatorActor, class UAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
	

}

