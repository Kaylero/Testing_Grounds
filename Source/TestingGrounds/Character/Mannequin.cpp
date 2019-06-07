// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannequin.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "../Weapons/Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FP_Camera"));
	CameraComponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	FP_Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Arms"));
	FP_Arms->SetOnlyOwnerSee(true);
	FP_Arms->SetupAttachment(CameraComponent);
	FP_Arms->bCastDynamicShadow = false;
	FP_Arms->CastShadow = false;
	FP_Arms->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	FP_Arms->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	if (GunBlueprint == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	Gun->AttachToComponent(FP_Arms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); //Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor																													
	Gun->AnimInstance = FP_Arms->GetAnimInstance();

	if (InputComponent != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
	
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

	
}

void AMannequin::PullTrigger()
{
	Gun->OnFire();
}


