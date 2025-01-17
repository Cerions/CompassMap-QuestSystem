// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReachLocationActor.generated.h"

class UObjectStateComponent;
class UCapsuleComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocationReached, AReachLocationActor*, Source);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocationLeave, AReachLocationActor*, Source);

UCLASS()
class COMPASSMAPPROJECT_API AReachLocationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AReachLocationActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UObjectStateComponent* ObjectStateComp {};

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComp {};

	FOnLocationReached OnLocationReached;

	FOnLocationLeave OnLocationLeave;

protected:
	
	virtual void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void EnterReachLocationArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ExitReachLocationArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void HideQuestIcon(bool Show, UObjectStateComponent* ObjectStateRef);

	/*UPROPERTY(EditAnywhere)
	UWidgetComponent* QuestIcon {};*/
};
