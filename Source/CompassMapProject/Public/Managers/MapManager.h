// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/GameplayStructures.h"
#include "MapManager.generated.h"

class UObjectStateComponent;

UCLASS()
class COMPASSMAPPROJECT_API AMapManager : public AActor
{
	GENERATED_BODY()
	
public:	

	AMapManager();

protected:

	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	TArray<UObjectStateComponent*> ObjectsState;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void InitManager();

	UFUNCTION()
	void GetAllPOI(TArray<FPOIConfigRow>& POIConfig);

	UFUNCTION()
	TArray<FMarkerPosition> GetDynamicMarkers() { return DynamicMarkers; }

	UFUNCTION()
	void AddToDiscoveredPOIs(FName DiscoveredPOI, FVector POILocation) { DiscoveredPOIs.Add(DiscoveredPOI, POILocation); }

	UFUNCTION()
	void RemoveFromDiscoveredPOIs(FName RemovedPOI) { DiscoveredPOIs.Remove(RemovedPOI); }

	UFUNCTION()
	void UpdateDynamicMarkers(TArray<UObjectStateComponent*> Markers);

	UFUNCTION()
	void ChangeDynamicMarkers(FMarkerPosition Marker, bool Add);

private:

	//UPROPERTY()
	//TArray<FName> DiscoveredPOIs {};

	UPROPERTY()
	TMap<FName, FVector> DiscoveredPOIs {};

	UPROPERTY()
	TArray<FMarkerPosition> DynamicMarkers {};

	UFUNCTION()
	void OnObjectStateLoaded(UObjectStateComponent* LoadedObject);

	UFUNCTION()
	void OnObjectStateUnloaded(UObjectStateComponent* UnloadedObject);
};
