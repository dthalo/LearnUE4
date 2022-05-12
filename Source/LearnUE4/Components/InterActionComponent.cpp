// Fill out your copyright notice in the Description page of Project Settings.


#include "InterActionComponent.h"
#include "../Interfaces/GameInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UInterActionComponent::UInterActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInterActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInterActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInterActionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();



	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + EyeRotation.Vector() * 1000;

	//FHitResult HitResult;
	//GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, End, ObjectQueryParams);
	//AActor* HitActor = HitResult.GetActor();
	//if (HitActor)
	//{
	//	//HitActor->Implements<IGameInterface>();//这个API编不过，内部调用了StaticClass函数
	//	UClass* HitActorClass = HitActor->GetClass();
	//	
	//	if (HitActorClass->ImplementsInterface(UGameInterface::StaticClass()))
	//	{
	//		IGameInterface::Execute_Interact(HitActor, Cast<APawn>(MyOwner));
	//		UE_LOG(LogTemp, Warning, TEXT("open"));
	//	}
	//}

	float Radius = 30;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	TArray<FHitResult> Hits;

	bool bHitBlocking = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bHitBlocking ? FColor::Green : FColor::Red;
	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UGameInterface>())
			{
				IGameInterface::Execute_Interact(HitActor, Cast<APawn>(MyOwner));

				break;
			}
		}

		DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Radius,32,LineColor,false,2.0);
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}