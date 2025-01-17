// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayConstants.generated.h"

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UGameplayConstants : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	FVector2D MinMaxCompassIconArrowDistanceZ = FVector2D(-30.f, 30.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	TSoftObjectPtr<UDataTable> POITable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	TSoftObjectPtr<UDataTable> ObjectsTransform = nullptr;
};
