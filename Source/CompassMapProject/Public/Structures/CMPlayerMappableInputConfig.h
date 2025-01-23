// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayStructures.h"
#include "CMPlayerMappableInputConfig.generated.h"

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UCMPlayerMappableInputConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ContextName = "";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FPlayerMappableInputConfigByPlatform> ContextsByPlatform;
};
