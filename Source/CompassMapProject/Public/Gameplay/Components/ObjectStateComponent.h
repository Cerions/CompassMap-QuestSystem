// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMPASSMAPPROJECT_API UObjectStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FName ObjectID {};

	UFUNCTION()
	void ObjectReady();

protected:
	
	virtual void BeginPlay() override;

		
};
