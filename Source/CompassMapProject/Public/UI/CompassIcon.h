// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structures/GameplayStructures.h"
#include "CompassIcon.generated.h"

class AActor;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UCompassIcon : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	UPROPERTY(meta = (BindWidget))
	UImage* ArrowImage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DistanceFromPlayer;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* DistanceFromPlayerContainer;

	UPROPERTY()
	AActor* TargetActor {};

	UPROPERTY()
	float Distance = 0.f;

	UPROPERTY()
	int32 IconZOrder = 0;

public:

	UPROPERTY()
	FPOIConfigRow MarkerData;

	UFUNCTION()
	void SetupWidget(AActor* ActorRef, const FPOIConfigRow& Row, const FVector& POILocation);

	UFUNCTION()
	void UpdateMarker();

	UFUNCTION()
	const int32 GetIconZOrder();

	UFUNCTION()
	const float GetDistanceFromPlayer() { return Distance; };

	UFUNCTION()
	void DisableDistanceText(bool Disable);
};
