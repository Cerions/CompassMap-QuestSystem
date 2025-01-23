// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/CMEventManager.h"

void UCMEventManager::InitManager(UCMGameInstance* InstanceOwner)
{
	if (InstanceOwner)
	{
		GInstanceRef = InstanceOwner;
	}
}

void UCMEventManager::OnCharacterRefSetEvent(ACMPlayer* PC)
{
	OnCharacterRefSet.Broadcast(PC);
}

//void UCMEventManager::OnPOIsActivatedEvent()
//{
//	OnPOIsActivated.Broadcast();
//}

void UCMEventManager::OnStepReachedEvent()
{
	OnStepReached.Broadcast();
}

void UCMEventManager::OnQuestUnlockEvent(const FName& QuestID)
{
	OnQuestUnlock.Broadcast(QuestID);
}

void UCMEventManager::OnObjectStateLoadedEvent(UObjectStateComponent* ObjectStateComp)
{
	OnObjectStateLoaded.Broadcast(ObjectStateComp);
}

void UCMEventManager::OnObjectStateUnloadedEvent(UObjectStateComponent* ObjectStateComp)
{
	OnObjectStateUnloaded.Broadcast(ObjectStateComp);
}

void UCMEventManager::OnBeginQuestTargetEvent(bool Show, UObjectStateComponent* ObjectStateRef)
{
	OnBeginQuestTarget.Broadcast(Show, ObjectStateRef);
}

void UCMEventManager::OnMarkerNotifyEvent(const FPOIConfigRow& Marker, bool Add)
{
	OnMarkerNotify.Broadcast(Marker, Add);
}

void UCMEventManager::OnNotifyQuestStartEvent(FName QuestID, int32 CurrentStepIndex, ENotifyType NotifyType)
{
	OnNotifyQuestStart.Broadcast(QuestID, CurrentStepIndex, NotifyType);
}

void UCMEventManager::OnEndStepEvent(const FName& QuestID, const int32 CurrentStepIndex)
{
	OnEndStep.Broadcast(QuestID, CurrentStepIndex);
}

void UCMEventManager::OnEnemyDeathEvent(APawn* Enemy)
{
	OnEnemyDeath.Broadcast(Enemy);
}
