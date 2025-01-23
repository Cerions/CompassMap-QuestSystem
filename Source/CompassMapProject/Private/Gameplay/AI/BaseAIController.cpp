// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AI/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Gameplay/AI/BlackboardKeyManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "Gameplay/Interfaces/EnemyInterface.h"
#include "Managers/MapManager.h"
#include "FunctionLibraries/GameplayFunctionLibrary.h"

ABaseAIController::ABaseAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

bool ABaseAIController::GetValueAsBool(const FName& iKey) const
{
	check(BlackboardComponent);
	return BlackboardComponent->GetValue<UBlackboardKeyType_Bool>(GetKey(iKey));
}

float ABaseAIController::GetValueAsFloat(const FName& iKey) const
{
	check(BlackboardComponent);
	return BlackboardComponent->GetValue<UBlackboardKeyType_Float>(GetKey(iKey));
}

int32 ABaseAIController::GetValueAsInt(const FName& iKey) const
{
	check(BlackboardComponent);
	return BlackboardComponent->GetValue<UBlackboardKeyType_Int>(GetKey(iKey));
}

FVector ABaseAIController::GetValueAsVector(const FName& iKey) const
{
	check(BlackboardComponent);
	return BlackboardComponent->GetValue<UBlackboardKeyType_Vector>(GetKey(iKey));
}

UObject* ABaseAIController::GetValueAsObject(const FName& iKey) const
{
	check(BlackboardComponent);
	return BlackboardComponent->GetValue<UBlackboardKeyType_Object>(GetKey(iKey));
}

FName ABaseAIController::GetValueAsFName(const FName& iKey) const
{
	check(BlackboardComponent);
	return BlackboardComponent->GetValue<UBlackboardKeyType_Name>(GetKey(iKey));
}

uint8 ABaseAIController::GetValueAsEnum(const FName& iKey) const
{
	check(BlackboardComponent);
	return BlackboardComponent->GetValue<UBlackboardKeyType_Enum>(GetKey(iKey));
}

bool ABaseAIController::SetValueAsBool(const FName& iKey, bool Value)
{
	check(BlackboardComponent);
	return BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(GetKey(iKey), Value);
}

bool ABaseAIController::SetValueAsFloat(const FName& iKey, float Value)
{
	check(BlackboardComponent);
	return BlackboardComponent->SetValue<UBlackboardKeyType_Float>(GetKey(iKey), Value);
}

bool ABaseAIController::SetValueAsInt(const FName& iKey, int32 Value)
{
	check(BlackboardComponent);
	return BlackboardComponent->SetValue<UBlackboardKeyType_Int>(GetKey(iKey), Value);
}

bool ABaseAIController::SetValueAsVector(const FName& iKey, const FVector& Value)
{
	check(BlackboardComponent);
	return BlackboardComponent->SetValue<UBlackboardKeyType_Vector>(GetKey(iKey), Value);
}

bool ABaseAIController::SetValueAsObject(const FName& iKey, UObject* Value)
{
	check(BlackboardComponent);
	return BlackboardComponent->SetValue<UBlackboardKeyType_Object>(GetKey(iKey), Value);
}

bool ABaseAIController::SetValueAsFName(const FName& iKey, const FName& Value)
{
	check(BlackboardComponent);
	return BlackboardComponent->SetValue<UBlackboardKeyType_Name>(GetKey(iKey), Value);
}

bool ABaseAIController::SetValueAsEnum(const FName& iKey, uint8 Value)
{
	check(BlackboardComponent);
	return BlackboardComponent->SetValue<UBlackboardKeyType_Enum>(GetKey(iKey), Value);
}

FBlackboard::FKey ABaseAIController::GetKey(const FName& iKey) const
{
	if (BlackboardKeyManager)
	{
		return BlackboardKeyManager->GetKey(iKey);
	}
	return FBlackboard::InvalidKey;
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(CheckMapTimerHandler, this, &ABaseAIController::MapCheckLoop, 0.2f, true);
	}
}

void ABaseAIController::InitBT()
{
	auto* BehaviorTree = GetBehaviorTree();
	if (!BehaviorTree)
	{
		return;
	}
	BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	if (!BlackboardKeyManager)
	{
		BlackboardKeyManager = NewObject<UBlackboardKeyManager>();
		BlackboardKeyManager->Initialize(BlackboardComponent);
	}
	BehaviorTreeComponent->StartTree(*BehaviorTree);
	SetValueAsObject(UBlackboardKeyManager::SelfActorKey, GetPawn());
}

void ABaseAIController::InterruptBT()
{
	BehaviorTreeComponent->StopTree(EBTStopMode::Forced);
}

UBehaviorTree* ABaseAIController::GetBehaviorTree()
{
	IEnemyInterface* IEnemy = Cast<IEnemyInterface>(GetPawn());
	if (IEnemy)
	{
		return IEnemy->GetBehaviorTree();
	}
	return nullptr;
}

// CHECKARE SE POSSIBILE TOGLIERE
void ABaseAIController::MapCheckLoop()
{
	if (!bWaitForMapLoad)
	{
		OnMapLoaded();
	}
	AMapManager* MapManager = UGameplayFunctionLibrary::GetMapManagerActor(this);
	if (MapManager && GetPawn())
	{
		/*if (MapManager->IsMapLoaded(GetPawn()->GetActorLocation()))
		{
			OnMapLoaded();
		}*/
		OnMapLoaded();
	}
}

void ABaseAIController::OnMapLoaded()
{
	if (GetWorld() && CheckMapTimerHandler.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(CheckMapTimerHandler);
	}

	InitBT();
	OnAIControllerLoadedDelegate.Broadcast();
}

void ABaseAIController::OnUnPossess()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
	Super::OnUnPossess();
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

