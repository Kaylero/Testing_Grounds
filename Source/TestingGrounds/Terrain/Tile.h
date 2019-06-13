// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius);

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* BoxMesh;

	UFUNCTION(BlueprintCallable, CAtegory = "Pool")
	void SetPool(UActorPool* Pool);

private:

	UActorPool* Pool;

	bool GetEmptyLocation(FVector& OutLocation, float Radius);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Location, float Rotation);
	bool CanSpawnAtLocation(FVector Location, float Radius);

};
