// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/QuestSystem/StepBase.h"
#include "Structures/GameplayStructures.h"
#include "KillStep.generated.h"

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UKillStep : public UStepBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> EnemyIDs {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<APawn>, int32> EnemyTypes {};

	UPROPERTY(VisibleAnywhere)
	FName MarkerRowName = "KillStep";

	void InitStep() override;

	void EndStep() override;

	void UpdateStep(float DeltaTime) override;

	TArray<FStepTargetInfo> GetStepTargetsData() override;

protected:

	void QuestTargetRegister(UObjectStateComponent* ObjectStateComponent) override;

	void QuestTargetUnregister(UObjectStateComponent* ObjectStateComponent) override;

	void CheckIsStepComplete() override;

	FName GetRowName() override;

private:

	UPROPERTY()
	TArray<FName> EnemyIDsProgress = {};

	UPROPERTY()
	TMap<TSubclassOf<APawn>, int32> EnemyTypesProgress = {};

	UFUNCTION()
	void EnemyKilled(APawn* Enemy);
};
