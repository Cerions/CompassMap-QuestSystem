// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structures/GameplayStructures.h"
#include "CMEventManager.generated.h"

class UCMGameInstance;
class ACompassMapProjectCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterRefSet, ACompassMapProjectCharacter*, PC);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPOIsActivated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStepReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectStateLoaded, UObjectStateComponent*, ObjectStateComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectStateUnloaded, UObjectStateComponent*, ObjectStateComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeginQuestTarget, bool, Show, UObjectStateComponent*, ObjectStateRef);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMarkerNotify, const FPOIConfigRow&, Marker, bool, Add);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnNotifyQuestStart, FName, QuestID, int32, CurrentStepIndex, ENotifyType, NotifyType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEndStep, const FName&, QuestID, const int32, CurrentStepIndex);

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


	void OnCharacterRefSetEvent(ACompassMapProjectCharacter* PC);
	FOnCharacterRefSet OnCharacterRefSet;

	void OnPOIsActivatedEvent();
	FOnPOIsActivated OnPOIsActivated;

	void OnStepReachedEvent();
	FOnStepReached OnStepReached;

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

	void OnEndStepEvent(const FName& QuestID, const int32 CurrentStepIndex);
	FOnEndStep OnEndStep;

protected:

	UPROPERTY()
	UCMGameInstance* GInstanceRef {};
};
