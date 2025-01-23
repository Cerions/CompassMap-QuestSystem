// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HUDManager.generated.h"

class UBaseHUD;
class AGameplayGameMode;
class ACMPlayer;

UCLASS()
class COMPASSMAPPROJECT_API AHUDManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AHUDManager();

	UFUNCTION()
	void CreateHUD();

protected:

	UFUNCTION()
	void SetPlayerCharacter(ACMPlayer* PC);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBaseHUD> BaseHUD;

	UPROPERTY()
	UBaseHUD* ActualHUD {};

	UPROPERTY()
	AGameplayGameMode* GameplayGameMode {};

	UPROPERTY()
	ACMPlayer* PlayerCharacter {};

};
