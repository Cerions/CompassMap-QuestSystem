// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseHUD.h"
#include "UI/CompassMap.h"
#include "UI/QuestNotifyContainer.h"

void UBaseHUD::InitWidgets()
{
	if (WidgetOwner)
	{
		CompassMap->InitWidget(WidgetOwner);
	}
	QuestNotifyContainer->Init();
}

void UBaseHUD::Init(AActor* HUDOwner)
{
	WidgetOwner = HUDOwner;
	InitWidgets();
}
