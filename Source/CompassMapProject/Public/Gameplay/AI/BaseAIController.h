// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BaseAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBlackboardKeyManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAIControllerLoadedDelegate);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class COMPASSMAPPROJECT_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABaseAIController();

    /// BLACKBOARD GETTER

	UFUNCTION(BlueprintCallable)
	bool GetValueAsBool(const FName& iKey) const;
	UFUNCTION(BlueprintCallable)
	float GetValueAsFloat(const FName& iKey) const;
	UFUNCTION(BlueprintCallable)
	int32 GetValueAsInt(const FName& iKey) const;
	UFUNCTION(BlueprintCallable)
	FVector GetValueAsVector(const FName& iKey) const;
	UFUNCTION(BlueprintCallable)
	UObject* GetValueAsObject(const FName& iKey) const;
	UFUNCTION(BlueprintCallable)
	FName GetValueAsFName(const FName& iKey) const;
	UFUNCTION(BlueprintCallable)
	uint8 GetValueAsEnum(const FName& iKey) const;

	/// BLACKBOARD SETTER

	UFUNCTION(BlueprintCallable)
	bool SetValueAsBool(const FName& iKey, bool Value);
	UFUNCTION(BlueprintCallable)
	bool SetValueAsFloat(const FName& iKey, float Value);
	UFUNCTION(BlueprintCallable)
	bool SetValueAsInt(const FName& iKey, int32 Value);
	UFUNCTION(BlueprintCallable)
	bool SetValueAsVector(const FName& iKey, const FVector& Value);
	UFUNCTION(BlueprintCallable)
	bool SetValueAsObject(const FName& iKey, UObject* Value);
	UFUNCTION(BlueprintCallable)
	bool SetValueAsFName(const FName& iKey, const FName& Value);
	UFUNCTION(BlueprintCallable)
	bool SetValueAsEnum(const FName& iKey, uint8 Value);

    
	void InitBT();
	void InterruptBT();

	UPROPERTY(BlueprintAssignable)
	FOnAIControllerLoadedDelegate OnAIControllerLoadedDelegate;

protected:

	void OnPossess(APawn* InPawn) override;

	FBlackboard::FKey GetKey(const FName& iKey) const;
    
	virtual UBehaviorTree* GetBehaviorTree();

	UFUNCTION()
	virtual void MapCheckLoop();

	UFUNCTION()
	virtual void OnMapLoaded();

	void OnUnPossess() override;

	void BeginPlay() override;

protected:

	UPROPERTY()
	FTimerHandle CheckMapTimerHandler;

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;

	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComponent = nullptr;

	UPROPERTY(Transient)
	UBlackboardKeyManager* BlackboardKeyManager = nullptr;
    
	UPROPERTY(EditDefaultsOnly)
	bool bWaitForMapLoad = true;    

};
