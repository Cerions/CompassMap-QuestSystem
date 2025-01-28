// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuestInfoElement.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"
#include "Components/TextBlock.h"
#include "Gameplay/QuestSystem/StepBase.h"

void UQuestInfoElement::NativeConstruct()
{
	Super::NativeConstruct();
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnEndStep.AddUniqueDynamic(this, &UQuestInfoElement::RemoveWidget);
	}
}

void UQuestInfoElement::NativeDestruct()
{
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnEndStep.RemoveDynamic(this, &UQuestInfoElement::RemoveWidget);
	}
	Super::NativeDestruct();
}

void UQuestInfoElement::RemoveWidget(const FName& QuestID, const int32 CurrentStepIndex)
{
	if (CloseAnimation)
	{
		CloseAnimationFinished.BindUFunction(this, FName("ManageCloseAnimationFinished"));
		this->BindToAnimationFinished(CloseAnimation, CloseAnimationFinished);
		PlayAnimation(CloseAnimation);
		bIsPendingClose = true;
	}
	else
	{
		ManageCloseAnimationFinished();
	}
}

void UQuestInfoElement::ManageCloseAnimationFinished()
{
	if (OnNotifyEnd.IsBound())
	{
		OnNotifyEnd.Broadcast(this);
	}
}

void UQuestInfoElement::InitNotifyElement(UQuestData* QuestData, int32 CurrentStepIndex, bool PlayEnterAnimation /*= false*/)
{
	Super::InitNotifyElement(QuestData, CurrentStepIndex, PlayEnterAnimation);

	QuestName->SetText(QuestData->Name);
	if (QuestData->Steps.Num() > 0)
	{
		QuestStepDescription->SetText(QuestData->Steps[CurrentStepIndex]->Description);
	}
}

void UQuestInfoElement::StartNotify()
{
	Super::StartNotify();

	if (OpenAnimation && bPlayAnimationEnter)
	{
		PlayAnimation(OpenAnimation);
		bPlayAnimationEnter = false;
	}
}
