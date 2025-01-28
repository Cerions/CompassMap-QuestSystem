// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NotifyElement.h"
#include "Components/TextBlock.h"
#include "Structures/GameplayStructures.h"

void UNotifyElement::InitNotifyElement(UQuestData* QuestData, int32 CurrentStepIndex, bool PlayEnterAnimation /*= false*/)
{
	Super::InitNotifyElement(QuestData, CurrentStepIndex, PlayEnterAnimation);
	if (QuestData)
	{
		QuestName->SetText(QuestData->Name);
	}
}

