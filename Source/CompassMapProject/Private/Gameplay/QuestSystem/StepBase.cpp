// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/QuestSystem/StepBase.h"
#include "FunctionLibraries/GameplayFunctionLibrary.h"
#include "Structures/GameplayConstants.h"
#include "Managers/QuestManager.h"
#include "Managers/CMEventManager.h"
#include "Managers/MapManager.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Gameplay/Components/ObjectStateComponent.h"
#include "Gameplay/QuestSystem/QuestBase.h"

#pragma optimize("", off)

void UStepBase::InitStep()
{
	IsStepActive = false;

	if (QuestManagerRef && QuestOwnerRef && QuestManagerRef->GetWorld())
	{
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(QuestManagerRef->GetWorld());
		if (EM)
		{
			EM->OnObjectStateLoaded.AddUniqueDynamic(this, &UStepBase::QuestTargetRegister);
			EM->OnObjectStateUnloaded.AddUniqueDynamic(this, &UStepBase::QuestTargetUnregister);

		}

		AMapManager* MapManager = UGameplayFunctionLibrary::GetMapManagerActor(QuestManagerRef->GetWorld());

		if (MapManager)
		{
			for (UObjectStateComponent* ObjectState : MapManager->ObjectsState)
			{
				if (ObjectState)
				{
					QuestTargetRegister(ObjectState);
				}
			}
		}
	}
}

void UStepBase::StartStep()
{
	IsStepActive = true;

	CheckIsStepComplete();
}

void UStepBase::UpdateStep(float DeltaTime)
{

}

void UStepBase::CheckIsStepComplete()
{

}

void UStepBase::EndStep()
{
	if (QuestManagerRef && QuestManagerRef->GetWorld())
	{
		IsStepActive = false;

		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(QuestManagerRef->GetWorld());
		if (EM)
		{
			EM->OnObjectStateLoaded.RemoveDynamic(this, &UStepBase::QuestTargetRegister);
			EM->OnObjectStateUnloaded.RemoveDynamic(this, &UStepBase::QuestTargetUnregister);

			while (RegisteredTargets.Num() > 0)
			{
				if (RegisteredTargets[0])
				{
					CompassMarkerNotify(FMarkerPosition(RegisteredTargets[0]->ObjectID, GetRowName(), FVector::ZeroVector), false);
					EM->OnBeginQuestTargetEvent(false, RegisteredTargets[0]);
				}
				RegisteredTargets.RemoveAt(0);
			}
		}

		while (TargetsCompassPosition.Num() > 0)
		{
			CompassMarkerNotify(FMarkerPosition(TargetsCompassPosition[0].ObjectID, GetRowName(), FVector::ZeroVector), false);
			TargetsCompassPosition.RemoveAt(0);
		}

		StepCompleted.Broadcast();
	}
}

void UStepBase::UninitStep()
{

}

void UStepBase::CompassMarkerNotify(FMarkerPosition Marker, bool Add)
{
	if (QuestManagerRef && QuestManagerRef->GetWorld())
	{
		AMapManager* MapManager = UGameplayFunctionLibrary::GetMapManagerActor(QuestManagerRef->GetWorld());

		if (MapManager)
		{
			MapManager->ChangeDynamicMarkers(Marker, Add);
		}
	}
}

void UStepBase::StoreCompassPositions(TArray<FName> Targets)
{
	if (QuestManagerRef && QuestOwnerRef && QuestManagerRef->GetWorld())
	{
		UGameplayConstants* GameplayConstantsRef = Cast<UGameplayConstants>(UGameplayFunctionLibrary::GetGameplayConstants(QuestManagerRef->GetWorld()));
		if (GameplayConstantsRef)
		{
			for (FName TargetID : Targets)
			{
				FObjectStateWorldRef ObjectInfo = UGameplayFunctionLibrary::FindObjectState(TargetID, QuestManagerRef->GetWorld());
				FMarkerPosition MarkerPosition = FMarkerPosition(TargetID, GetRowName(), ObjectInfo.StoredPosition.GetLocation(), ObjectInfo.StoredExtension);
				CompassMarkerNotify(MarkerPosition, true);
				TargetsCompassPosition.Add(MarkerPosition);
			}
		}
	}
}

FName UStepBase::GetRowName()
{
	return NAME_None;
}

void UStepBase::UpdateCompassMarkers()
{
	if (QuestManagerRef && QuestManagerRef->GetWorld())
	{
		AMapManager* MapManager = UGameplayFunctionLibrary::GetMapManagerActor(QuestManagerRef->GetWorld());

		if (MapManager)
		{
			MapManager->UpdateDynamicMarkers(RegisteredTargets);
		}
	}
}

void UStepBase::QuestTargetRegister(UObjectStateComponent* ObjectStateComponent)
{
	// QuestArea
}

void UStepBase::QuestTargetUnregister(UObjectStateComponent* ObjectStateComponent)
{
	// QuestArea
}

void UStepBase::ShowQuestTarget(UObjectStateComponent* ObjectStateComponent)
{
	if (ObjectStateComponent && ObjectStateComponent->ObjectID != NAME_None && QuestManagerRef && QuestManagerRef->GetWorld())
	{
		RegisteredTargets.Add(ObjectStateComponent);
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(QuestManagerRef->GetWorld());
		if (EM)
		{
			EM->OnBeginQuestTargetEvent(true, ObjectStateComponent);
		}
	}
}

void UStepBase::HideQuestTarget(UObjectStateComponent* ObjectStateComponent)
{
	if (ObjectStateComponent && ObjectStateComponent->ObjectID != NAME_None && QuestManagerRef && QuestManagerRef->GetWorld())
	{
		RegisteredTargets.Remove(ObjectStateComponent);
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(QuestManagerRef->GetWorld());
		if (EM)
		{
			EM->OnBeginQuestTargetEvent(false, ObjectStateComponent);
		}
	}
}

void UStepBase::RemoveQuestTarget(UObjectStateComponent* ObjectStateComponent)
{

}
