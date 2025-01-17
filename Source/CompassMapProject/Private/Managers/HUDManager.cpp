// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/HUDManager.h"
#include "UI/BaseHUD.h"
#include "CompassMapProject/CompassMapProjectCharacter.h"
#include "FunctionLibraries/GameplayFunctionLibrary.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"

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

void AHUDManager::SetPlayerCharacter(ACompassMapProjectCharacter* PC)
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
	}
}

void AHUDManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnCharacterRefSet.RemoveDynamic(this, &AHUDManager::SetPlayerCharacter);
	}
}

