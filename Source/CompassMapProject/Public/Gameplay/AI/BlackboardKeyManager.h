// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BlackboardKeyManager.generated.h"

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UBlackboardKeyManager : public UObject
{
	GENERATED_BODY()
	
public:

	void Initialize(UBlackboardComponent* BlackboardComponent);
	FBlackboard::FKey GetKey(const FName& iKey);

	static const FName SelfActorKey;
	static const FName StartingForwardKey;
	static const FName TargetKey;
	static const FName IsEngagedKey;
	static const FName CanSeePlayerKey;

protected:

	TMap<FName, FBlackboard::FKey> Keys;
};
