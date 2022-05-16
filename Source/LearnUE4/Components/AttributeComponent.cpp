// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	Health = 100;
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

bool UAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr,this,Health,Delta);
	return true;
}

