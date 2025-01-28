// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHUD.generated.h"

class UCompassMap;
class UQuestNotifyContainer;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UBaseHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	AActor* WidgetOwner {};

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCompassMap* CompassMap {};

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UQuestNotifyContainer* QuestNotifyContainer {};

	UFUNCTION()
	virtual void InitWidgets();

public:

	UFUNCTION()
	virtual void Init(AActor* HUDOwner);
};
