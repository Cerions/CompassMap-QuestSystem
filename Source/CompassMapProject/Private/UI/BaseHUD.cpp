// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseHUD.h"
#include "UI/CompassMap.h"

void UBaseHUD::InitWidgets()
{
	if (WidgetOwner)
	{
		CompassMap->InitWidget(WidgetOwner);
	}	
}

void UBaseHUD::Init(AActor* HUDOwner)
{
	WidgetOwner = HUDOwner;
	InitWidgets();
}
