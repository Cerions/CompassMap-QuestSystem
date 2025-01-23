// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/QuestSystem/KillStep.h"
#include "Managers/QuestManager.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"
#include "Gameplay/Components/ObjectStateComponent.h"

void UKillStep::InitStep()
{
	if (QuestManagerRef)
	{
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(QuestManagerRef->GetWorld());
		if (EM)
		{
			EM->OnEnemyDeath.AddDynamic(this, &UKillStep::EnemyKilled);
		}
	}
	
	EnemyTypesProgress = EnemyTypes;
	EnemyIDsProgress = EnemyIDs;
	//EnemyIDs.Append(FakeTargets);

	StoreCompassPositions(EnemyIDsProgress);
	Super::InitStep();
}

void UKillStep::EndStep()
{
	if (QuestManagerRef)
	{
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(QuestManagerRef->GetWorld());
		if (EM)
		{
			EM->OnEnemyDeath.RemoveDynamic(this, &UKillStep::EnemyKilled);
		}
	}
	Super::EndStep();
}

void UKillStep::UpdateStep(float DeltaTime)
{
	Super::UpdateStep(DeltaTime);
	UpdateCompassMarkers();
}

TArray<FStepTargetInfo> UKillStep::GetStepTargetsData()
{
	TArray<FStepTargetInfo> Result;
	for (FName EnemyID : EnemyIDs)
	{
		Result.Add(FStepTargetInfo(EnemyID, nullptr, 1));
	}
	for (TPair<TSubclassOf<APawn>, int32> EnemyType : EnemyTypes)
	{
		Result.Add(FStepTargetInfo("", EnemyType.Key, EnemyType.Value));
	}

	return Result;
}

void UKillStep::QuestTargetRegister(UObjectStateComponent* ObjectStateComponent)
{
	Super::QuestTargetRegister(ObjectStateComponent);

	if (ObjectStateComponent && QuestManagerRef && ObjectStateComponent->GetOwner())
	{
		APawn* Enemy = Cast<APawn>(ObjectStateComponent->GetOwner());
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(QuestManagerRef->GetWorld());
		if (Enemy && EM)
		{
			if (EnemyIDsProgress.Contains(ObjectStateComponent->ObjectID))
			{
				ShowQuestTarget(ObjectStateComponent);
			}
			else
			{
				for (TPair<TSubclassOf<APawn>, int32> EnemyType : EnemyTypesProgress)
				{
					if (ObjectStateComponent->ObjectID != NAME_None && Enemy->GetClass() == EnemyType.Key)
					{
						ShowQuestTarget(ObjectStateComponent);
					}
				}
			}
		}
	}
}

void UKillStep::QuestTargetUnregister(UObjectStateComponent* ObjectStateComponent)
{
	Super::QuestTargetUnregister(ObjectStateComponent);

	if (ObjectStateComponent && QuestManagerRef && ObjectStateComponent->GetOwner())
	{
		APawn* Enemy = Cast<APawn>(ObjectStateComponent->GetOwner());
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(QuestManagerRef->GetWorld());
		if (Enemy && EM)
		{
			if (EnemyIDsProgress.Contains(ObjectStateComponent->ObjectID))
			{
				HideQuestTarget(ObjectStateComponent);
			}
			else
			{
				for (TPair<TSubclassOf<APawn>, int32> EnemyType : EnemyTypesProgress)
				{
					if (ObjectStateComponent->ObjectID != NAME_None && Enemy->GetClass() == EnemyType.Key)
					{
						HideQuestTarget(ObjectStateComponent);
					}
				}
			}
		}
	}
}

void UKillStep::CheckIsStepComplete()
{
	if (EnemyIDsProgress.Num() == 0 && EnemyTypesProgress.Num() == 0)
	{
		EndStep();
	}
}

FName UKillStep::GetRowName()
{
	return MarkerRowName;
}

void UKillStep::EnemyKilled(APawn* Enemy)
{
	UObjectStateComponent* ObjectState = Cast<UObjectStateComponent>(Enemy->GetComponentByClass(UObjectStateComponent::StaticClass()));
	if (ObjectState)
	{
		if (EnemyIDsProgress.Contains(ObjectState->ObjectID))
		{
			RemoveQuestTarget(ObjectState);
			EnemyIDsProgress.Remove(ObjectState->ObjectID);
			StepProgress.Broadcast();
		}

		UClass* EnemyClass = Enemy->GetClass();
		if (EnemyClass)
		{
			if (EnemyTypesProgress.Contains(EnemyClass))
			{
				EnemyTypesProgress[EnemyClass]--;
				if (EnemyTypesProgress[EnemyClass] <= 0)
				{
					EnemyTypesProgress.Remove(EnemyClass);
					RemoveQuestTargetByType(EnemyClass);
				}
				else
				{
					RemoveQuestTarget(ObjectState);
				}

				StepProgress.Broadcast();
			}
		}
	}

	CheckIsStepComplete();
}
