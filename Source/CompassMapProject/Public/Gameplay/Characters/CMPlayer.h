// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CompassMapProject/CompassMapProjectCharacter.h"
#include "Gameplay/Interfaces/PlayerInterface.h"
#include "CMPlayer.generated.h"

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API ACMPlayer : public ACompassMapProjectCharacter, public IPlayerInterface
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	float SphereRadius = 120.f;

	UCameraComponent* GetActiveCamera() override;

protected:

	UFUNCTION(BlueprintCallable)
	void SphereAttack();
};
