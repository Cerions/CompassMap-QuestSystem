// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structures/GameplayStructures.h"
#include "CompassMap.generated.h"

class UImage;
class UPanelWidget;
class UCanvasPanel;
class IPlayerInterface;
class AActor;
class UCompassIcon;
class AMapManager;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UCompassMap : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	AActor* OwnerWidget = nullptr;

	IPlayerInterface* PlayerInterface {};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CompassImage {};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* CompassCanvas {};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* MarkerContainer {};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* ClampCanvas {};

	/*UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UQuestAreaIcon* QuestAreaIcon {};*/

	UPROPERTY(BlueprintReadWrite)
	TArray<UCompassIcon*> CompassIcons;

	UPROPERTY()
	AMapManager* MapManager {};

	UPROPERTY()
	TArray<FName> HiddenPOI {};

	UPROPERTY(EditAnywhere, Category = "Design")
	float NorthCompassOffset = 0.f;

	UPROPERTY()
	float Progress = 0.f;

	UPROPERTY(EditAnywhere, Category = "Design")
	float TickValue = 0.f;

	UPROPERTY(EditAnywhere, Category = "Design")
	float OverlapDifferenceValue = 50.f;

	UPROPERTY(EditAnywhere, Category = "Design")
	float DistanceBetweenCardinalPoint = 1100.f;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void UpdateCompassDirection();

	UFUNCTION()
	void UpdateMarkerPosition();

	UFUNCTION(BlueprintCallable)
	float GetScreenLocation(FVector TargetLocation);

	UFUNCTION()
	void OnPOIsActivated();

	UFUNCTION()
	void UpdatePOIs(const FPOIConfigRow& POI, bool NewDiscovery);

	UFUNCTION()
	void UpdateMarkers(const FPOIConfigRow& Row, bool Add);

	UFUNCTION()
	void CreateMarker(const FPOIConfigRow& Row);

	UFUNCTION()
	void RemoveMarker(const FPOIConfigRow& Row);

	UFUNCTION()
	void HidePOI(FName POIID, bool bHide);

	UFUNCTION()
	void OnQuestAreaEnter(FName QuestAreaID);

	UFUNCTION()
	void OnQuestAreaLeave(FName QuestAreaID);

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCompassIcon> CompassIconClass;

	UFUNCTION()
	void InitWidget(AActor* WidgetOwner);
};
