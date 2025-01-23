// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class ACMPlayer;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACMPlayer> PlayerCharacterClass;

	UPROPERTY()
	ACMPlayer* CharRef {};

private:

	void BeginPlay() override;

	UFUNCTION()
	void SpawnCharacter();
};
