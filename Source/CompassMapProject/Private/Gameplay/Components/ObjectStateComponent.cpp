// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Components/ObjectStateComponent.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"

void UObjectStateComponent::ObjectReady()
{
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);
	if (EM)
	{
		EM->OnObjectStateLoadedEvent(this);
	}
}

void UObjectStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

