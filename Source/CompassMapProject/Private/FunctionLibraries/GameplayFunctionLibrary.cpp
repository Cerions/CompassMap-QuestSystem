// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GameplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/GameplayGameMode.h"
#include "PlayerControllers/BasePlayerController.h"
#include "System/CMGameInstance.h"
#include "Managers/MapManager.h"
#include "Structures/GameplayConstants.h"
#include "Gameplay/Components/ObjectStateComponent.h"
#include "Gameplay/Characters/CMPlayer.h"

UGameplayConstants* UGameplayFunctionLibrary::GetGameplayConstants(UObject* WorldContext)
{
	UCMGameInstance* GInstance = Cast<UCMGameInstance>(UGameplayStatics::GetGameInstance(WorldContext));
	if (GInstance)
	{
		return GInstance->GameplayConstants;
	}

	return nullptr;
}

ACMPlayer* UGameplayFunctionLibrary::GetPlayerCharacter(UObject* WorldContext)
{
	AGameplayGameMode* GameplayGameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(WorldContext));
	if (GameplayGameMode && GameplayGameMode->PlayerRef)
	{
		return GameplayGameMode->PlayerRef->CharRef;
	}

	return nullptr;
}

ABasePlayerController* UGameplayFunctionLibrary::GetPlayerController(UObject* WorldContext)
{
	AGameplayGameMode* GameplayGameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(WorldContext));
	if (GameplayGameMode && GameplayGameMode->PlayerRef)
	{
		return GameplayGameMode->PlayerRef;
	}

	return nullptr;
}

AMapManager* UGameplayFunctionLibrary::GetMapManagerActor(UObject* WorldContext)
{
	AMapManager* MapManagerActor = {};
	AGameplayGameMode* GM = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(WorldContext));
	if (GM)
	{
		MapManagerActor = GM->MapManager;
	}

	return MapManagerActor;
}

AQuestManager* UGameplayFunctionLibrary::GetQuestManager(UObject* WorldContext)
{
	AGameplayGameMode* GM = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(WorldContext));
	if (GM)
	{
		return GM->QuestManager;
	}
	return nullptr;
}

void UGameplayFunctionLibrary::AddPOI(FName NewPOI, FVector POILocation, UObject* WorldContext)
{
	/*if (AMapManager* MapManager = GetMapManagerActor(WorldContext))
	{
		MapManager->AddToDiscoveredPOIs(NewPOI, POILocation);
	}*/
}

void UGameplayFunctionLibrary::RemovePOI(FName NewPOI, UObject* WorldContext)
{
	if (AMapManager* MapManager = GetMapManagerActor(WorldContext))
	{
		MapManager->RemoveFromDiscoveredPOIs(NewPOI);
	}
}

FObjectStateWorldRef UGameplayFunctionLibrary::FindObjectState(FName ObjectID, UObject* WorldContext)
{
	AMapManager* MapManager = GetMapManagerActor(WorldContext);
	UGameplayConstants* GameplayConstantsRef = GetGameplayConstants(WorldContext);

	for (UObjectStateComponent* ObjectState : MapManager->ObjectsState)
	{
		if (ObjectState && ObjectState->GetOwner() && ObjectState->ObjectID == ObjectID)
		{
			FObjectStateWorldRef Obj;
			Obj.SpawnedObject = ObjectState;
			Obj.StoredPosition = ObjectState->GetOwner()->GetTransform();
			FQuestActorTransformDataRow* Row = GameplayConstantsRef->ObjectsTransform.LoadSynchronous()->FindRow<FQuestActorTransformDataRow>(ObjectID, TEXT(""));
			if (Row)
			{
				Obj.StoredExtension = Row->AreaSize;
			}

			return Obj;
		}
	}

	FQuestActorTransformDataRow* Row = GameplayConstantsRef->ObjectsTransform.LoadSynchronous()->FindRow<FQuestActorTransformDataRow>(ObjectID, TEXT(""));
	if (Row)
	{
		FObjectStateWorldRef Obj;
		Obj.SpawnedObject = nullptr;
		Obj.StoredPosition = Row->ObjectTransform;
		Obj.StoredExtension = Row->AreaSize;
	}

	return FObjectStateWorldRef();
}

//bool UGameplayFunctionLibrary::IsPOIDiscovered(FName POI, UObject* WorldContext)
//{
//	if (AMapManager* MapManager = GetMapManagerActor(WorldContext))
//	{
//		return MapManager->GetDiscoveredPOIs().Contains(POI);
//	}
//
//	return false;
//}

