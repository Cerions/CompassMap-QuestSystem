// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/MapManager.h"
#include "FunctionLibraries/GameplayFunctionLibrary.h"
#include "Structures/GameplayConstants.h"
#include "Gameplay/Components/ObjectStateComponent.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"

AMapManager::AMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMapManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapManager::InitManager()
{
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);
	if (EM)
	{
		EM->OnObjectStateLoaded.AddDynamic(this, &AMapManager::OnObjectStateLoaded);
		EM->OnObjectStateUnloaded.AddDynamic(this, &AMapManager::OnObjectStateUnloaded);
	}
}

// trasformarlo in TMAP?
void AMapManager::GetAllPOI(TArray<FPOIConfigRow>& POIConfig)
{
	UGameplayConstants* GameplayConstants = UGameplayFunctionLibrary::GetGameplayConstants(this);

	if(GameplayConstants && GameplayConstants->POITable.LoadSynchronous())
	{
		TArray<FName> DiscoveredPOIIDs {};
		DiscoveredPOIs.GenerateKeyArray(DiscoveredPOIIDs);
		for (FName POI : DiscoveredPOIIDs)
		{
			FPOIConfigRow* Row = GameplayConstants->POITable.LoadSynchronous()->FindRow<FPOIConfigRow>(POI, TEXT(""));

			if (Row)
			{
				POIConfig.Add(*Row);
			}
		}

		// Dynamic markers
		for (FMarkerPosition Marker : DynamicMarkers)
		{
			FPOIConfigRow* Row = GameplayConstants->POITable.LoadSynchronous()->FindRow<FPOIConfigRow>(Marker.Type, TEXT(""));
			if (Row)
			{
				FPOIConfigRow NewRow = *Row;

				NewRow.Location = Marker.Location;
				NewRow.Id = Marker.ObjectID;
				NewRow.AreaSize = Marker.AreaSize;
				POIConfig.Add(NewRow);
			}
		}
	}
}

void AMapManager::UpdateDynamicMarkers(TArray<UObjectStateComponent*> Markers)
{
	for (int32 i = 0; i < Markers.Num(); i++)
	{
		for (int32 j = 0; j < DynamicMarkers.Num(); j++)
		{
			if (Markers[i] && Markers[i]->GetOwner())
			{
				if (Markers[i]->ObjectID == DynamicMarkers[j].ObjectID)
				{
					DynamicMarkers[j].Location = Markers[i]->GetOwner()->GetActorLocation();
				}
			}
		}
	}
}

void AMapManager::ChangeDynamicMarkers(FMarkerPosition Marker, bool Add)
{
	if (Add && (DynamicMarkers.Contains(Marker) || Marker.ObjectID == NAME_None))
	{
		return;
	}

	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);

	if (EM)
	{
		if (Add)
		{
			DynamicMarkers.AddUnique(Marker);
		}
		else
		{
			DynamicMarkers.Remove(Marker);
		}

		UGameplayConstants* Constants = UGameplayFunctionLibrary::GetGameplayConstants(this);
		if (Constants && Constants->POITable.LoadSynchronous())
		{
			FPOIConfigRow* Row = Constants->POITable.LoadSynchronous()->FindRow<FPOIConfigRow>(Marker.Type, TEXT(""));
			if (Row)
			{
				Row->Location = Marker.Location;
				Row->Id = Marker.ObjectID;
				EM->OnMarkerNotifyEvent(*Row, Add);
			}
		}
	}
}

void AMapManager::OnObjectStateLoaded(UObjectStateComponent* LoadedObject)
{
	ObjectsState.Add(LoadedObject);
}

void AMapManager::OnObjectStateUnloaded(UObjectStateComponent* UnloadedObject)
{
	ObjectsState.Remove(UnloadedObject);
}

