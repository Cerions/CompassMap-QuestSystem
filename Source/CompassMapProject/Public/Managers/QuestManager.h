// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

class UQuestBase;

UCLASS()
class COMPASSMAPPROJECT_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:

	AQuestManager();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FName StartingQuest = "Q01";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	TObjectPtr<UDataTable> QuestTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	TSoftClassPtr<UQuestBase> QuestClass;

	UFUNCTION()
	void CreateAndStartQuest(FName QuestID);

	UFUNCTION()
	UQuestBase* CreateQuest(FName QuestID, UQuestData* Data);

	UFUNCTION()
	void GoToNextStep(UQuestBase* CurrentQuest);

	UFUNCTION()
	void HandleStepEnd(UQuestBase* CurrentQuest);

	UFUNCTION()
	void HandleQuestEnd(UQuestBase* CurrentQuest);

	void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	UQuestBase* ActualInProgressQuest {};

	UFUNCTION()
	void UnlockQuest(FName QuestToUnlock);

	UFUNCTION()
	void GoToNextQuest(FName NextQuestID);

};
