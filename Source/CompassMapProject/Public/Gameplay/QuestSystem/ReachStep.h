// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/QuestSystem/StepBase.h"
#include "ReachStep.generated.h"

class ABasePlayerController;
class AReachLocationActor;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UReachStep : public UStepBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ReachTargetID {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool UseReachTargetActor = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsLeavingAreaStep = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!UseReachTargetActor", EditConditionHides))
	float ReachArea = 1000.f;

	UPROPERTY(VisibleAnywhere)
	FName MarkerRowName = "ReachStep";

	void InitStep() override;

	void UpdateStep(float DeltaTime) override;

protected:

	void QuestTargetRegister(UObjectStateComponent* ObjectStateComponent) override;

	void QuestTargetUnregister(UObjectStateComponent* ObjectStateComponent) override;

	void CheckIsStepComplete() override;

	UFUNCTION()
	void OnLocationReach(AReachLocationActor* Source);

	FName GetRowName() override;

private:

	UPROPERTY()
	ABasePlayerController* PlayerRef {};

};
