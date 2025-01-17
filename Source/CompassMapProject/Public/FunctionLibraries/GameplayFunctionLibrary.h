// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayFunctionLibrary.generated.h"

class UGameplayConstants;
class ACompassMapProjectCharacter;
class AMapManager;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static UGameplayConstants* GetGameplayConstants(UObject* WorldContext);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static ACompassMapProjectCharacter* GetPlayerCharacter(UObject* WorldContext);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static AMapManager* GetMapManagerActor(UObject* WorldContext);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void AddPOI(FName NewPOI, FVector POILocation, UObject* WorldContext);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void RemovePOI(FName NewPOI, UObject* WorldContext);

	/*UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static bool IsPOIDiscovered(FName POI, UObject* WorldContext);*/

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FObjectStateWorldRef FindObjectState(FName ObjectID, UObject* WorldContext);
};
