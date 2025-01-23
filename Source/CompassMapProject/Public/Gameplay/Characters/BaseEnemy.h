// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gameplay/Interfaces/EnemyInterface.h"
#include "BaseEnemy.generated.h"

class UBehaviorTree;
class UObjectStateComponent;
class AEnemyAIController;
//class USplineComponent;

UCLASS()
class COMPASSMAPPROJECT_API ABaseEnemy : public ACharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:

	ABaseEnemy();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	UBehaviorTree* BehaviorTree {};

	UPROPERTY()
	AEnemyAIController* AIController{};

	virtual void BeginPlay() override;

	UFUNCTION()
	AActor* GetTarget();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObjectStateComponent* ObjectStateComp {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "180.0", UIMin = "0.0", UIMax = "180.0"), Category = "Design")
	float PeripheralVision = 70.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Design")
	FName TrackID = "";

	/*UPROPERTY()
	USplineComponent* CurrentSpline {};*/

	UPROPERTY()
	float DistanceOnSpline = 0.f;

	UPROPERTY()
	FVector ClosestPointOnSpline;

	UPROPERTY()
	FVector StartingPosition;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	UFUNCTION()
	AEnemyAIController* GetAIController() const;

	void OnHit() override;

private:

	UFUNCTION()
	void OnAIControllerLoaded();

};
