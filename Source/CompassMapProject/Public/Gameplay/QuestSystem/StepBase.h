// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structures/GameplayStructures.h"
#include "StepBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStepCompleted);

class AQuestManager;
class UQuestBase;
class UObjectStateComponent;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInLineNew)
class COMPASSMAPPROJECT_API UStepBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description = {};

	UPROPERTY()
	AQuestManager* QuestManagerRef {};

	UPROPERTY()
	UQuestBase* QuestOwnerRef {};

	UPROPERTY()
	TArray<UObjectStateComponent*> RegisteredTargets {};

	UPROPERTY()
	TArray<FMarkerPosition> TargetsCompassPosition;

	UPROPERTY()
	FStepCompleted StepCompleted;

	UFUNCTION()
	virtual void InitStep();

	UFUNCTION()
	virtual void StartStep();

	UFUNCTION()
	virtual void UpdateStep(float DeltaTime);

	UFUNCTION()
	virtual void CheckIsStepComplete();

	UFUNCTION()
	virtual void EndStep();

	UFUNCTION()
	virtual void UninitStep();

protected:

	UPROPERTY()
	bool IsStepActive = false;

	UFUNCTION()
	virtual void CompassMarkerNotify(FMarkerPosition Marker, bool Add);

	UFUNCTION()
	virtual void StoreCompassPositions(TArray<FName> Targets);

	UFUNCTION()
	virtual FName GetRowName();

	UFUNCTION()
	void UpdateCompassMarkers();

	UFUNCTION()
	virtual void QuestTargetRegister(UObjectStateComponent* ObjectStateComponent);

	UFUNCTION()
	virtual void QuestTargetUnregister(UObjectStateComponent* ObjectStateComponent);

	UFUNCTION()
	void ShowQuestTarget(UObjectStateComponent* ObjectStateComponent);

	UFUNCTION()
	void HideQuestTarget(UObjectStateComponent* ObjectStateComponent);

	UFUNCTION()
	void RemoveQuestTarget(UObjectStateComponent* ObjectStateComponent);
};
