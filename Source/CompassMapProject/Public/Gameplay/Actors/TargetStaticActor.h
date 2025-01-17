// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetBaseActor.h"
#include "TargetStaticActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class COMPASSMAPPROJECT_API ATargetStaticActor : public ATargetBaseActor
{
	GENERATED_BODY()
	
public:	
	
	ATargetStaticActor();

protected:
	
	virtual void BeginPlay() override;

};
