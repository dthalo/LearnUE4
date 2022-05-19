// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Projectile/MagicProjectile.h"
#include "../Components/InterActionComponent.h"
#include "../Components/AttributeComponent.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");

	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp->SetupAttachment(SpringArmComp);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	InterActionComp = CreateDefaultSubobject<UInterActionComponent>("InterActionComp");

	AttributeComp = CreateDefaultSubobject<UAttributeComponent>("AttributeComp");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ABaseCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("BlackHoleAttack", IE_Pressed, this, &ABaseCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ABaseCharacter::Dash);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ABaseCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void ABaseCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;
	AddMovementInput(ControlRot.Vector(), Value);
}

void ABaseCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;
	FVector RightVec = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVec, Value);

}

void ABaseCharacter::PrimaryAttack()
{
	/*if (GetMesh()->DoesSocketExist(FName("Muzzle_01")))
	{
		PlayAnimMontage(AttackMontage);
		GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ABaseCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	}*/

	PlayAnimMontage(AttackMontage);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ABaseCharacter::PrimaryAttack_TimeElapsed, AttackAnimDelay);
}

void ABaseCharacter::PrimaryAttack_TimeElapsed()
{
	/*if (ensure(ProjectileClass))
	{
		FVector SocketLocation = GetMesh()->GetSocketLocation(FName("Muzzle_01"));
		FTransform SpawnTM = FTransform(GetControlRotation(), SocketLocation);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}*/
	SpawnProjectile(ProjectileClass);
}

void ABaseCharacter::PrimaryInteract()
{
	if (InterActionComp)
	{
		InterActionComp->PrimaryInteract();
	}
}


void ABaseCharacter::BlackHoleAttack()
{
	PlayAnimMontage(AttackMontage);
	GetWorldTimerManager().SetTimer(TimerHandle_BlackHoleAttack, this, &ABaseCharacter::BlackHoleAttack_TimeElapsed, AttackAnimDelay);
}

void ABaseCharacter::BlackHoleAttack_TimeElapsed()
{
	SpawnProjectile(BlackHoleProjectileClass);
}

void ABaseCharacter::Dash()
{
	PlayAnimMontage(AttackMontage);
	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ABaseCharacter::Dash_TimeElapsed, AttackAnimDelay);
}

void ABaseCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void ABaseCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		FVector HandleLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		//Ignore Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
		
		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = CameraComp->GetComponentLocation() + GetControlRotation().Vector() * 5000;
		
		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}

		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandleLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandleLocation);

		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);

	}
}