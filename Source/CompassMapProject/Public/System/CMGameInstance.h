// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CMGameInstance.generated.h"

class UGameplayConstants;
class UCMEventManager;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UCMGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	friend class UGameplayFunctionLibrary;
	friend class USingletonFunctionLibrary;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
	UGameplayConstants* GameplayConstants {};

	UPROPERTY(EditDefaultsOnly, Category = "ClassDefinitions")
	TSubclassOf<UCMEventManager> EventManagerClass;

private:

	UPROPERTY()
	UCMEventManager* EventManagerInstance {};
};
