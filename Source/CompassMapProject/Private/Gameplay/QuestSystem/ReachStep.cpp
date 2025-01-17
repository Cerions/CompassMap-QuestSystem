// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/QuestSystem/ReachStep.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/GameplayGameMode.h"
#include "Managers/QuestManager.h"
#include "Gameplay/Components/ObjectStateComponent.h"
#include "Gameplay/Actors/ReachLocationActor.h"
#include "PlayerControllers/BasePlayerController.h"

void UReachStep::InitStep()
{
	if (QuestManagerRef)
	{
		AGameplayGameMode* GameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(QuestManagerRef->GetWorld()));
		if (GameMode)
		{
			PlayerRef = GameMode->PlayerRef;
		}
	}
	StoreCompassPositions(TArray<FName>{ ReachTargetID });
	Super::InitStep();
}

void UReachStep::UpdateStep(float DeltaTime)
{
	if (!UseReachTargetActor)
	{
		CheckIsStepComplete();
	}

	Super::UpdateStep(DeltaTime);
}

void UReachStep::QuestTargetRegister(UObjectStateComponent* ObjectStateComponent)
{
	Super::QuestTargetRegister(ObjectStateComponent);

	if (ObjectStateComponent && ObjectStateComponent->GetOwner())
	{
		if (ObjectStateComponent->ObjectID == ReachTargetID)
		{
			ShowQuestTarget(ObjectStateComponent);
			if (UseReachTargetActor)
			{
				AReachLocationActor* ReachActor = Cast<AReachLocationActor>(ObjectStateComponent->GetOwner());
				if (ReachActor)
				{
					if (IsLeavingAreaStep)
					{
						ReachActor->OnLocationLeave.AddDynamic(this, &UReachStep::OnLocationReach);
					}
					else
					{
						ReachActor->OnLocationReached.AddDynamic(this, &UReachStep::OnLocationReach);
					}
				}
			}
		}
	}
}

void UReachStep::QuestTargetUnregister(UObjectStateComponent* ObjectStateComponent)
{
	Super::QuestTargetUnregister(ObjectStateComponent);

	if (ObjectStateComponent && ObjectStateComponent->ObjectID == ReachTargetID)
	{
		if (ObjectStateComponent->ObjectID == ReachTargetID)
		{
			HideQuestTarget(ObjectStateComponent);
			if (UseReachTargetActor)
			{
				AReachLocationActor* ReachActor = Cast<AReachLocationActor>(ObjectStateComponent->GetOwner());
				if (ReachActor)
				{
					if (ReachActor->OnLocationLeave.IsBound())
					{
						ReachActor->OnLocationLeave.RemoveDynamic(this, &UReachStep::OnLocationReach);
					}
					if(ReachActor->OnLocationReached.IsBound())
					{
						ReachActor->OnLocationReached.AddDynamic(this, &UReachStep::OnLocationReach);
					}
				}
			}
		}
	}
}

void UReachStep::CheckIsStepComplete()
{
	if (!UseReachTargetActor)
	{
		for (UObjectStateComponent* Target : RegisteredTargets)
		{
			if (Target && PlayerRef)
			{
				if (FVector::Dist(PlayerRef->GetPawn()->GetActorLocation(), Target->GetOwner()->GetActorLocation()) < ReachArea)
				{
					EndStep();
					return;
				}
			}
		}
	}
}

void UReachStep::OnLocationReach(AReachLocationActor* Source)
{
	if (Source)
	{
		UObjectStateComponent* ObjectStateComp = Cast<UObjectStateComponent>(Source->GetComponentByClass(UObjectStateComponent::StaticClass()));
		for (UObjectStateComponent* Target : RegisteredTargets)
		{
			if (ObjectStateComp && Target && Target->ObjectID == ObjectStateComp->ObjectID)
			{
				EndStep();
				return;
			}
		}
	}
}

FName UReachStep::GetRowName()
{
	return MarkerRowName;
}
