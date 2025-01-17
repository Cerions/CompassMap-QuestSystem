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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FName StartingQuest = "Q01";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	TSoftObjectPtr<UDataTable> QuestTable = nullptr;

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

protected:
	
	virtual void BeginPlay() override;

};
