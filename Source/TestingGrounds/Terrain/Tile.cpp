// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	CastSphere(GetActorLocation(), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	FMath::RandPointInBox(Bounds);

	int NumberToSpwan = FMath::RandRange(MinSpawn, MaxSpawn);

	for(size_t i = 0; i < NumberToSpwan; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor* SpawnedActor = GetWorld()->SpawnActor(ToSpawn);
		SpawnedActor->SetActorRelativeLocation(SpawnPoint);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		Location + FVector(0.001f, 0.001f, 0.001f),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

	if (HasHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("HitResult %s"),  *HitResult.Actor->GetName());
	}

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), Location, Radius, 100, ResultColor, true, 100);

	return HasHit;
}

