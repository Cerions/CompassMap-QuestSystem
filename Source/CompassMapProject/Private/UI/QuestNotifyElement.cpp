// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuestNotifyElement.h"

void UQuestNotifyElement::NativeConstruct()
{
	Super::NativeConstruct();
}

void UQuestNotifyElement::NativeDestruct()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerHandle);
	Super::NativeDestruct();
}

void UQuestNotifyElement::ManageNotifyAnimationFinished()
{
	if (OnNotifyEnd.IsBound())
	{
		OnNotifyEnd.Broadcast(this);
	}
}

void UQuestNotifyElement::StartNotify()
{
	if (!bIsFixed)
	{
		if (NotifyAnim)
		{
			NotifyAnimationFinished.BindUFunction(this, FName("ManageNotifyAnimationFinished"));
			this->BindToAnimationFinished(NotifyAnim, NotifyAnimationFinished);
			PlayAnimation(NotifyAnim);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UQuestNotifyElement::ManageNotifyAnimationFinished, TimerDuration, false);
		}
	}
}

void UQuestNotifyElement::InitNotifyElement(UQuestData* QuestData, int32 CurrentStepIndex, bool PlayEnterAnim /*= false*/)
{
	NotifyQuestData = QuestData;
	NotifyCurrentStepIndex = CurrentStepIndex;
	bPlayAnimationEnter = PlayEnterAnim;
}
