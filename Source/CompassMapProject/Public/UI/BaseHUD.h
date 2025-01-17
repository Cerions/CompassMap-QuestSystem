// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHUD.generated.h"

class UCompassMap;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UBaseHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	AActor* WidgetOwner = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCompassMap* CompassMap;

	UFUNCTION()
	virtual void InitWidgets();

public:

	UFUNCTION()
	virtual void Init(AActor* HUDOwner);
};
