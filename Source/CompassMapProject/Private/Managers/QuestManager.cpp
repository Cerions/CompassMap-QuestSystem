// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/QuestManager.h"
#include "Structures/GameplayStructures.h"
#include "Gameplay/QuestSystem/QuestBase.h"

#pragma optimize("", off)

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
	}
}

void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	
	CreateAndStartQuest(StartingQuest);
}


