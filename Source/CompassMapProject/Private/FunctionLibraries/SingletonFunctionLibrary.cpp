// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "System/CMGameInstance.h"
#include "Managers/CMEventManager.h"

UCMEventManager* USingletonFunctionLibrary::GetEventManager(UObject* WorldObjectContext)
{
	UCMGameInstance* GInstance = Cast<UCMGameInstance>(UGameplayStatics::GetGameInstance(WorldObjectContext));
	if (GInstance)
	{
		if (GInstance->EventManagerInstance == nullptr)
		{
			if (!GInstance->EventManagerClass)
			{
				UE_LOG(LogTemp, Warning, TEXT("NO Class Definition for Event Manager!"))
				return nullptr;
			}
			GInstance->EventManagerInstance = NewObject<UCMEventManager>(GInstance, GInstance->EventManagerClass, FName("EventManager"));
			if (GInstance->EventManagerInstance)
			{
				GInstance->EventManagerInstance->InitManager(GInstance);
			}
		}
		return GInstance->EventManagerInstance;
	}

	return nullptr;
}
