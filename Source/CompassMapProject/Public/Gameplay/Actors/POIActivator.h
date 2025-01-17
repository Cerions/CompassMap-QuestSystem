// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "POIActivator.generated.h"

class USphereComponent;
class ATargetStaticActor;
class AReachLocationActor;

UCLASS()
class COMPASSMAPPROJECT_API APOIActivator : public AActor
{
	GENERATED_BODY()
	
public:	

	APOIActivator();

	UPROPERTY(EditAnywhere)
	TArray<AReachLocationActor*> ReachLocationActors;

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* TriggerSphere {};

	UFUNCTION()
	void OnPOIActivatorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
