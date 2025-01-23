// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AI/BlackboardKeyManager.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName UBlackboardKeyManager::SelfActorKey{ TEXT("SelfActor") };
const FName UBlackboardKeyManager::StartingForwardKey{ TEXT("StartingForward") };
const FName UBlackboardKeyManager::TargetKey{ TEXT("Target") };
const FName UBlackboardKeyManager::IsEngagedKey{ TEXT("IsEngaged") };
const FName UBlackboardKeyManager::CanSeePlayerKey{ TEXT("CanSeePlayer") };

void UBlackboardKeyManager::Initialize(UBlackboardComponent* BlackboardComponent)
{
	Keys.Add(SelfActorKey, BlackboardComponent->GetKeyID(SelfActorKey));
	Keys.Add(StartingForwardKey, BlackboardComponent->GetKeyID(StartingForwardKey));
	Keys.Add(TargetKey, BlackboardComponent->GetKeyID(TargetKey));
	Keys.Add(IsEngagedKey, BlackboardComponent->GetKeyID(IsEngagedKey));
	Keys.Add(CanSeePlayerKey, BlackboardComponent->GetKeyID(CanSeePlayerKey));
}

FBlackboard::FKey UBlackboardKeyManager::GetKey(const FName& iKey)
{
	return Keys[iKey];
}
