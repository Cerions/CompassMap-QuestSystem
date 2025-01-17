// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Actors/TargetBaseActor.h"
#include "TargetStepActor.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API ATargetStepActor : public ATargetBaseActor
{
	GENERATED_BODY()
	
public:

	ATargetStepActor();

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* TriggerSphere {};

	UFUNCTION()
	void OnStepReached(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
