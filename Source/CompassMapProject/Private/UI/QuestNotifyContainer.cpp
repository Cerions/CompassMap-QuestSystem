// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuestNotifyContainer.h"
#include "Kismet/GameplayStatics.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"
#include "Managers/HUDManager.h"
#include "GameModes/GameplayGameMode.h"
#include "UI/QuestNotifyElement.h"
#include "Components/PanelWidget.h"

void UQuestNotifyContainer::NativeConstruct()
{
	Super::NativeConstruct();
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnNotifyQuestAddedToList.AddUniqueDynamic(this, &UQuestNotifyContainer::CheckNotifyToPrint);
	}
}

void UQuestNotifyContainer::NativeDestruct()
{
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnNotifyQuestAddedToList.RemoveDynamic(this, &UQuestNotifyContainer::CheckNotifyToPrint);
	}
	Super::NativeDestruct();
}

void UQuestNotifyContainer::CheckNotifyToPrint()
{
	AGameplayGameMode* GM = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM && GM->HUDManager)
	{
		ClearPendingQuestNotify();
		for (UQuestNotifyElement* Element : GM->HUDManager->NotifyElements)
		{
			if (Element->bIsFixed)
			{
				if (ActualFixedNotifyElement != Element && FixedElementContainer->GetAllChildren().Num() == 0
					&& ActualNotifyElement == nullptr)
				{
					ActualFixedNotifyElement = Element;
					FixedElementContainer->AddChild(ActualFixedNotifyElement);
					ActualFixedNotifyElement->OnNotifyEnd.AddUniqueDynamic(this, &UQuestNotifyContainer::RemoveFixedNotify);
					ActualFixedNotifyElement->StartNotify();
				}
			}
			else
			{
				if (ActualNotifyElement != Element && NotifyElementContainer->GetAllChildren().Num() == 0)
				{
					ActualNotifyElement = Element;
					NotifyElementContainer->AddChild(ActualNotifyElement);
					ActualNotifyElement->StartNotify();
					ActualNotifyElement->OnNotifyEnd.AddUniqueDynamic(this, &UQuestNotifyContainer::RemoveNotify);
				}
			}
		}
	}
}

void UQuestNotifyContainer::RemoveNotify(UQuestNotifyElement* NotifyElement)
{
	NotifyElement->OnNotifyEnd.RemoveDynamic(this, &UQuestNotifyContainer::RemoveNotify);
	AGameplayGameMode* GM = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM && GM->HUDManager)
	{
		GM->HUDManager->NotifyElements.Remove(NotifyElement);
		if (NotifyElement == ActualNotifyElement)
		{
			NotifyElement->RemoveFromParent();
			ActualNotifyElement = nullptr;
		}
		CheckNotifyToPrint();
	}
}

void UQuestNotifyContainer::RemoveFixedNotify(UQuestNotifyElement* NotifyElement)
{
	NotifyElement->OnNotifyEnd.RemoveDynamic(this, &UQuestNotifyContainer::RemoveFixedNotify);
	AGameplayGameMode* GM = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM && GM->HUDManager)
	{
		GM->HUDManager->NotifyElements.Remove(NotifyElement);
		if (NotifyElement == ActualFixedNotifyElement)
		{
			NotifyElement->RemoveFromParent();
			ActualFixedNotifyElement = nullptr;
		}
		CheckNotifyToPrint();
	}
}

void UQuestNotifyContainer::ClearPendingQuestNotify()
{
	AGameplayGameMode* GM = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM && GM->HUDManager)
	{
		TArray<UQuestNotifyElement*> ElementToRemove;
		for (UQuestNotifyElement* Element : GM->HUDManager->NotifyElements)
		{
			if (Element->bIsPendingClose)
			{
				ElementToRemove.Add(Element);
			}
		}

		for (UQuestNotifyElement* Element : ElementToRemove)
		{
			GM->HUDManager->NotifyElements.Remove(Element);
		}
	}
}

void UQuestNotifyContainer::Init()
{
	AGameplayGameMode* GM = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM && GM->HUDManager)
	{
		if (GM->HUDManager->NotifyElements.Num() > 0)
		{
			TArray<UQuestNotifyElement*> PendingCloseNotify{};
			for (UQuestNotifyElement* Notify : GM->HUDManager->NotifyElements)
			{
				if (Notify->bIsFixed && !Notify->bIsPendingClose)
				{
					Notify->OnNotifyEnd.AddUniqueDynamic(this, &UQuestNotifyContainer::RemoveFixedNotify);
				}
				else if(Notify->bIsFixed && Notify->bIsPendingClose)
				{
					PendingCloseNotify.Add(Notify);
				}
			}
			for (UQuestNotifyElement* Notify : PendingCloseNotify)
			{
				GM->HUDManager->NotifyElements.Remove(Notify);
			}
			PendingCloseNotify.Empty();
			CheckNotifyToPrint();
		}
	}
}

