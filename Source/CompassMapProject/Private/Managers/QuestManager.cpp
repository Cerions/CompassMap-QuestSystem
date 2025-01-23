// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/QuestManager.h"
#include "Structures/GameplayStructures.h"
#include "Gameplay/QuestSystem/QuestBase.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"

AQuestManager::AQuestManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AQuestManager::CreateAndStartQuest(FName QuestID)
{
	if (QuestID != NAME_None && QuestTable)
	{
		FQuestTableRow* Row = QuestTable->FindRow<FQuestTableRow>(QuestID, TEXT(""));
		if (Row)
		{
			UQuestBase* NewQuest = CreateQuest(QuestID, Row->QuestData);
			if (NewQuest)
			{
				NewQuest->InitQuest();
				NewQuest->StartQuest();
				ActualInProgressQuest = NewQuest;
			}
		}
	}
}

UQuestBase* AQuestManager::CreateQuest(FName QuestID, UQuestData* Data)
{
	UQuestBase* NewQuest = NewObject<UQuestBase>(this, QuestClass.LoadSynchronous());
	if (NewQuest)
	{
		NewQuest->QuestData = Data;
		NewQuest->QuestData->QuestID = QuestID;
		NewQuest->QuestManagerRef = this;
	}

	return NewQuest;
}

void AQuestManager::GoToNextStep(UQuestBase* CurrentQuest)
{
	if (CurrentQuest)
	{
		CurrentQuest->GoToNextStep();
	}
}

void AQuestManager::HandleStepEnd(UQuestBase* CurrentQuest)
{
	if (CurrentQuest)
	{
		EQuestStatus NextStatus = CurrentQuest->CheckIsLastStep() ? EQuestStatus::Ending : EQuestStatus::StepEnd;
		if (NextStatus == EQuestStatus::StepEnd)
		{
			GoToNextStep(CurrentQuest);
		}
		else if (NextStatus == EQuestStatus::Ending)
		{
			HandleQuestEnd(CurrentQuest);
		}
	}
}

void AQuestManager::HandleQuestEnd(UQuestBase* CurrentQuest)
{
	CurrentQuest->UninitQuest();

	ActualInProgressQuest = nullptr;

	if (CurrentQuest->QuestData->QuestToUnlock != "")
	{
		UnlockQuest(CurrentQuest->QuestData->QuestToUnlock);
	}
	if (CurrentQuest->QuestData->NextQuestID != NAME_None)
	{
		GoToNextQuest(CurrentQuest->QuestData->NextQuestID);
	}
}

void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	
	CreateAndStartQuest(StartingQuest);
}

void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActualInProgressQuest)
	{
		ActualInProgressQuest->UpdateQuest(DeltaTime);
	}
}

void AQuestManager::UnlockQuest(FName QuestToUnlock)
{
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnQuestUnlockEvent(QuestToUnlock);
	}
}

void AQuestManager::GoToNextQuest(FName NextQuestID)
{
	CreateAndStartQuest(NextQuestID);
}
