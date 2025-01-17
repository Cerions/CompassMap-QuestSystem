// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestBase.generated.h"

class UQuestData;
class AQuestManager;
class UStepBase;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UQuestBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
	UQuestData* QuestData = {};

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentStepIndex = 0;

	UPROPERTY()
	AQuestManager* QuestManagerRef {};

	UFUNCTION()
	void InitQuest();

	UFUNCTION()
	void StartQuest();

	UFUNCTION()
	void UpdateQuest(float DeltaTime);

	UFUNCTION()
	void StepCompleted();

	UFUNCTION()
	void GoToNextStep();

	UFUNCTION()
	void UninitQuest();

	UFUNCTION()
	void InitCurrentStep();

	UFUNCTION()
	void StartCurrentStep();

	UFUNCTION()
	void UninitCurrentStep();

	UFUNCTION()
	UStepBase* GetCurrentStep();

	UFUNCTION()
	bool CheckIsLastStep();


};
