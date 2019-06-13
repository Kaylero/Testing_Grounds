// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "InfiniteTerrainGameMode.h"


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
	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Pool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius)
{
	int NumberToSpwan = FMath::RandRange(MinSpawn, MaxSpawn);

	for(size_t i = 0; i < NumberToSpwan; i++)
	{
		FVector SpawnPoint;
		if (GetEmptyLocation(SpawnPoint, Radius))
		{
			float RandomRotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceActor(ToSpawn, SpawnPoint, RandomRotation);
		}
	}
}

void ATile::SetPool(UActorPool* Pool)
{
	this->Pool = Pool;

	PoisitioningNavMeshBoundsVolume(Pool);
}

void ATile::PoisitioningNavMeshBoundsVolume(UActorPool* Pool)
{
	NavMeshBoundsVolume = Pool->Checkout();

	if (!ensure(NavMeshBoundsVolume != nullptr))
	{
		return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
}

bool ATile::GetEmptyLocation(FVector& OutLocation, float Radius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	FMath::RandPointInBox(Bounds);

	const int MAX_ATTEMPTS = 30;

	FVector SpawnPoint;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		SpawnPoint = FMath::RandPointInBox(Bounds);

		if (CanSpawnAtLocation(SpawnPoint, Radius))
		{
			OutLocation = SpawnPoint;
			return true;
		}
	}

	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Location, float Rotation)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(Location);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedActor->SetActorRotation(FRotator(0, Rotation, 0));
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
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

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;

	//DrawDebugSphere(GetWorld(), Location, Radius, 100, ResultColor, true, 100);

	return !HasHit;
}

