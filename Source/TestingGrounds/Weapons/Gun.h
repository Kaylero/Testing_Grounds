// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class TESTINGGROUNDS_API AGun : public AActor
{
	GENERATED_BODY()

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(BlueprintReadWrite, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FireDelay;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LastFireTime;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnFire();

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABallProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimationFP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimationTP;

	UPROPERTY()
	class UAnimInstance* AnimInstanceFP;

	UPROPERTY()
	class UAnimInstance* AnimInstanceTP;

private:

	
};
