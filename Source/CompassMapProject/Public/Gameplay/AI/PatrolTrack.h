// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolTrack.generated.h"

class USplineComponent;
class ABaseEnemy;

UCLASS()
class COMPASSMAPPROJECT_API APatrolTrack : public AActor
{
	GENERATED_BODY()
	
public:	

	APatrolTrack();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FName TrackID = "";

	UPROPERTY(EditAnywhere)
	USplineComponent* SplineComp {};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<ABaseEnemy*> EnemiesOnTrack;

};
