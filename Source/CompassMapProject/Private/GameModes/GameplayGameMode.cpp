// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GameplayGameMode.h"
#include "Managers/HUDManager.h"
#include "Managers/MapManager.h"
#include "Managers/QuestManager.h"

void AGameplayGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	SpawnManagers();
}

void AGameplayGameMode::SpawnManagers()
{
	FActorSpawnParameters SpawnInfo;

	ensureMsgf(HUDManagerClass, TEXT("No Class Defined for HUD Manager"));
	HUDManager = GetWorld()->SpawnActor<AHUDManager>(HUDManagerClass, FTransform(), SpawnInfo);

	ensureMsgf(MapManagerClass, TEXT("No Class Defined for Map Manager"));
	MapManager = GetWorld()->SpawnActor<AMapManager>(MapManagerClass, FTransform(), SpawnInfo);
	MapManager->InitManager();

	ensureMsgf(MapManagerClass, TEXT("No Class Defined for Quest Manager"));
	QuestManager = GetWorld()->SpawnActor<AQuestManager>(QuestManagerClass, FTransform(), SpawnInfo);
}
