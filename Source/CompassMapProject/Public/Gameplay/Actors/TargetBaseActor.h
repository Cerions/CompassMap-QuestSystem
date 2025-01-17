// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetBaseActor.generated.h"

class UStaticMeshComponent;
class UObjectStateComponent;

UCLASS()
class COMPASSMAPPROJECT_API ATargetBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATargetBaseActor();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComp {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObjectStateComponent* ObjectStateComp {};

public:

	UPROPERTY(/*EditAnywhere*/)
	FName POIID = "";

};
