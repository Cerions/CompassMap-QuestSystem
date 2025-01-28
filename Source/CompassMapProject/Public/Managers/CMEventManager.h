// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structures/GameplayStructures.h"
#include "CMEventManager.generated.h"

class UCMGameInstance;
class ACMPlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterRefSet, ACMPlayer*, PC);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPOIsActivated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStepReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUnlock, const FName&, QuestID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectStateLoaded, UObjectStateComponent*, ObjectStateComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectStateUnloaded, UObjectStateComponent*, ObjectStateComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeginQuestTarget, bool, Show, UObjectStateComponent*, ObjectStateRef);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMarkerNotify, const FPOIConfigRow&, Marker, bool, Add);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnNotifyQuestStart, FName, QuestID, int32, CurrentStepIndex, ENotifyType, NotifyType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNotifyQuestAddedToList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEndStep, const FName&, QuestID, const int32, CurrentStepIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, APawn*, Enemy);

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UCMEventManager : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void InitManager(UCMGameInstance* InstanceOwner);


	void OnCharacterRefSetEvent(ACMPlayer* PC);
	FOnCharacterRefSet OnCharacterRefSet;

	/*void OnPOIsActivatedEvent();
	FOnPOIsActivated OnPOIsActivated;*/

	void OnStepReachedEvent();
	FOnStepReached OnStepReached;

	void OnQuestUnlockEvent(const FName& QuestID);
	FOnQuestUnlock OnQuestUnlock;

	void OnObjectStateLoadedEvent(UObjectStateComponent* ObjectStateComp);
	FOnObjectStateLoaded OnObjectStateLoaded;

	void OnObjectStateUnloadedEvent(UObjectStateComponent* ObjectStateComp);
	FOnObjectStateUnloaded OnObjectStateUnloaded;

	void OnBeginQuestTargetEvent(bool Show, UObjectStateComponent* ObjectStateRef);
	FOnBeginQuestTarget OnBeginQuestTarget;

	void OnMarkerNotifyEvent(const FPOIConfigRow& Marker, bool Add);
	FOnMarkerNotify OnMarkerNotify;

	void OnNotifyQuestStartEvent(FName QuestID, int32 CurrentStepIndex, ENotifyType NotifyType);
	FOnNotifyQuestStart OnNotifyQuestStart;

	void OnNotifyQuestAddedToListEvent();
	FOnNotifyQuestAddedToList OnNotifyQuestAddedToList;

	void OnEndStepEvent(const FName& QuestID, const int32 CurrentStepIndex);
	FOnEndStep OnEndStep;

	void OnEnemyDeathEvent(APawn* Enemy);
	FOnEnemyDeath OnEnemyDeath;
	

protected:

	UPROPERTY()
	UCMGameInstance* GInstanceRef {};
};
