// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/HUDManager.h"
#include "UI/BaseHUD.h"
#include "Gameplay/Characters/CMPlayer.h"
#include "FunctionLibraries/GameplayFunctionLibrary.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"
#include "Managers/QuestManager.h"
#include "UI/QuestNotifyElement.h"
#include "PlayerControllers/BasePlayerController.h"

AHUDManager::AHUDManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHUDManager::CreateHUD()
{
	if (BaseHUD)
	{
		ActualHUD = CreateWidget<UBaseHUD>(GetWorld()->GetGameInstance(), BaseHUD);
		if (ActualHUD)
		{
			ActualHUD->AddToViewport(0);
			if (PlayerCharacter)
			{
				ActualHUD->Init(PlayerCharacter);
			}			
		}
	}
}

void AHUDManager::SetPlayerCharacter(ACMPlayer* PC)
{
	PlayerCharacter = PC;

	CreateHUD();
}

void AHUDManager::BeginPlay()
{
	Super::BeginPlay();

	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnCharacterRefSet.AddUniqueDynamic(this, &AHUDManager::SetPlayerCharacter);
		//EM->OnNotifyQuestStart.AddUniqueDynamic(this, &AHUDManager::OnQuestStartEvent);
		EM->OnNotifyQuestStart.AddUniqueDynamic(this, &AHUDManager::AddNotifyQuestElement);
		EM->OnEndStep.AddUniqueDynamic(this, &AHUDManager::OnQuestStepEnd);
	}
	QuestManager = UGameplayFunctionLibrary::GetQuestManager(this);
}

void AHUDManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnCharacterRefSet.RemoveDynamic(this, &AHUDManager::SetPlayerCharacter);
		//EM->OnNotifyQuestStart.RemoveDynamic(this, &AHUDManager::OnQuestStartEvent);
		EM->OnNotifyQuestStart.RemoveDynamic(this, &AHUDManager::AddNotifyQuestElement);
		EM->OnEndStep.RemoveDynamic(this, &AHUDManager::OnQuestStepEnd);
	}
}

void AHUDManager::AddNotifyQuestElement(FName QuestID, int32 CurrentStepIndex, ENotifyType NotifyType)
{
	if (QuestManager && QuestManager->QuestTable)
	{
		UQuestData* QuestRow = QuestManager->QuestTable->FindRow<FQuestTableRow>(QuestID, "")->QuestData;
		if (NotifyClassElements.Contains(NotifyType) && QuestRow)
		{
			UQuestNotifyElement* NewNotify = CreateWidget<UQuestNotifyElement>(GetWorld()->GetGameInstance(), NotifyClassElements[NotifyType]);
			if (NewNotify)
			{
				bool bPlayerEnterAnimation = true;
				if (NewNotify->NotifyType == ENotifyType::StartStep)
				{
					for (UQuestNotifyElement* Notify : NotifyElements)
					{
						if (Notify->NotifyType == ENotifyType::StartQuest)
						{
							bPlayerEnterAnimation = false;
						}
					}
				}

				NewNotify->InitNotifyElement(QuestRow, CurrentStepIndex, bPlayerEnterAnimation);
				NotifyElements.Add(NewNotify);
				UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);
				if (EM)
				{
					EM->OnNotifyQuestAddedToListEvent();
				}
			}
		}
	}
	
}

void AHUDManager::OnQuestStepEnd(const FName& QuestID, const int32 CurrentStep)
{
	UQuestNotifyElement* QuestNotifyElementFound = nullptr;
	for (int32 k = 0; k < NotifyElements.Num(); k++)
	{
		if (NotifyElements[k]->NotifyType == ENotifyType::StartStep)
		{
			if (NotifyElements[k]->NotifyQuestData->QuestID == QuestID)
			{
				for (int32 i = 0; i < NotifyElements[k]->NotifyQuestData->Steps.Num(); i++)
				{
					if (i == CurrentStep)
					{
						QuestNotifyElementFound = NotifyElements[k];
						break;
					}
				}
			}
		}
	}

	if (QuestNotifyElementFound)
	{
		NotifyElements.Remove(QuestNotifyElementFound);
	}
}

