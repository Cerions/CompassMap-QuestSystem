// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/AI/BaseAIController.h"
#include "EnemyAIController.generated.h"

class ABaseEnemy;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API AEnemyAIController : public ABaseAIController
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void SetSightValues();

protected:

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void OnPossess(APawn* InPawn) override;

private:

	UPROPERTY()
	ABaseEnemy* Enemy {};
};
