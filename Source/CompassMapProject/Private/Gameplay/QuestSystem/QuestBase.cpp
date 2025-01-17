// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/QuestSystem/QuestBase.h"
#include "Structures/GameplayStructures.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"
#include "Managers/QuestManager.h"
#include "Gameplay/QuestSystem/StepBase.h"

#pragma optimize("", off)

void UQuestBase::InitQuest()
{
	CurrentStepIndex = 0;
	if (QuestData && QuestData->Steps.Num() > CurrentStepIndex)
	{
		InitCurrentStep();
	}
}

void UQuestBase::StartQuest()
{
	if (QuestData && QuestData->Steps.Num() > CurrentStepIndex)
	{
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);
		if (EM)
		{
			EM->OnNotifyQuestStartEvent(QuestData->QuestID, CurrentStepIndex, ENotifyType::StartQuest);
		}

		StartCurrentStep();
	}
}

void UQuestBase::UpdateQuest(float DeltaTime)
{
	if (QuestData && QuestData->Steps[CurrentStepIndex])
	{
		QuestData->Steps[CurrentStepIndex]->UpdateStep(DeltaTime);
	}
}

void UQuestBase::StepCompleted()
{
	if (QuestData && QuestData->Steps[CurrentStepIndex])
	{
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);
		if (EM)
		{
			EM->OnEndStepEvent(QuestData->QuestID, CurrentStepIndex);
		}
		QuestData->Steps[CurrentStepIndex]->StepCompleted.RemoveDynamic(this, &UQuestBase::StepCompleted);
		QuestManagerRef->HandleStepEnd(this);
	}
}

void UQuestBase::GoToNextStep()
{
	UninitCurrentStep();
	CurrentStepIndex++;
	InitCurrentStep();
	StartCurrentStep();
}

void UQuestBase::UninitQuest()
{
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);
	if (EM)
	{
		EM->OnNotifyQuestStartEvent(QuestData->QuestID, CurrentStepIndex, ENotifyType::EndQuest);
	}

	UninitCurrentStep();
}

void UQuestBase::InitCurrentStep()
{
	if (QuestData && QuestData->Steps[CurrentStepIndex])
	{
		QuestData->Steps[CurrentStepIndex]->QuestOwnerRef = this;
		QuestData->Steps[CurrentStepIndex]->QuestManagerRef = QuestManagerRef;
		QuestData->Steps[CurrentStepIndex]->TargetsCompassPosition.Empty();
		QuestData->Steps[CurrentStepIndex]->RegisteredTargets.Empty();
		QuestData->Steps[CurrentStepIndex]->InitStep();
	}
}

void UQuestBase::StartCurrentStep()
{
	if (QuestManagerRef)
	{
		UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);
		if (EM)
		{
			EM->OnNotifyQuestStartEvent(QuestData->QuestID, CurrentStepIndex, ENotifyType::StartStep);
		}
	}

	if (QuestData && QuestData->Steps[CurrentStepIndex])
	{
		QuestData->Steps[CurrentStepIndex]->StepCompleted.AddDynamic(this, &UQuestBase::StepCompleted);
		QuestData->Steps[CurrentStepIndex]->StartStep();
	}
}

void UQuestBase::UninitCurrentStep()
{
	if (QuestData && QuestData->Steps[CurrentStepIndex])
	{
		QuestData->Steps[CurrentStepIndex]->UninitStep();
	}
}

UStepBase* UQuestBase::GetCurrentStep()
{
	if (QuestData)
	{
		if (QuestData->Steps.IsValidIndex(CurrentStepIndex))
		{
			return QuestData->Steps[CurrentStepIndex];
		}
	}
	return nullptr;
}

bool UQuestBase::CheckIsLastStep()
{
	if (QuestData)
	{
		return CurrentStepIndex == QuestData->Steps.Num() - 1;
	}
	else
	{
		return true;
	}
}
