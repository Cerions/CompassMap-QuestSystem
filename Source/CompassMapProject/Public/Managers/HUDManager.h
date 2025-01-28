// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/GameplayStructures.h"
#include "HUDManager.generated.h"

class UBaseHUD;
class AGameplayGameMode;
class ACMPlayer;
class UQuestNotifyElement;
class AQuestManager;

UCLASS()
class COMPASSMAPPROJECT_API AHUDManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AHUDManager();

	UPROPERTY()
	TArray<UQuestNotifyElement*> NotifyElements;

	UFUNCTION()
	void CreateHUD();

protected:

	UFUNCTION()
	void SetPlayerCharacter(ACMPlayer* PC);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBaseHUD> BaseHUD;

	UPROPERTY()
	UBaseHUD* ActualHUD {};

	UPROPERTY()
	AGameplayGameMode* GameplayGameMode {};

	UPROPERTY()
	ACMPlayer* PlayerCharacter {};

	UPROPERTY()
	AQuestManager* QuestManager {};

	UPROPERTY(EditAnywhere, Category = "QuestNotify")
	TMap<ENotifyType, TSubclassOf<UQuestNotifyElement>> NotifyClassElements;

	UFUNCTION()
	void AddNotifyQuestElement(FName QuestID, int32 CurrentStepIndex, ENotifyType NotifyType);

private:

	UFUNCTION()
	void OnQuestStepEnd(const FName& QuestID, const int32 CurrentStep);

};
