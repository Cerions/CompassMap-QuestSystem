// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SingletonFunctionLibrary.generated.h"

class UCMEventManager;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API USingletonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Managers", meta = (WorldContext = "WorldContextObjects"))
	static UCMEventManager* GetEventManager(UObject* WorldObjectContext);
};
