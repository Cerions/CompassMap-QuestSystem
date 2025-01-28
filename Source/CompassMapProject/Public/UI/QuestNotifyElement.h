// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structures/GameplayStructures.h"
#include "QuestNotifyElement.generated.h"

class UQuestData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotifyEnd, UQuestNotifyElement*, NotifyElement);

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UQuestNotifyElement : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* NotifyAnim;

	UPROPERTY()
	FWidgetAnimationDynamicEvent NotifyAnimationFinished;

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere)
	float TimerDuration = 3.f;

	UPROPERTY()
	bool bPlayAnimationEnter = true;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	virtual void ManageNotifyAnimationFinished();

public:

	UPROPERTY(EditAnywhere)
	bool bIsFixed = false;

	UPROPERTY()
	bool bIsPendingClose = false;

	FOnNotifyEnd OnNotifyEnd;

	UPROPERTY()
	UQuestData* NotifyQuestData = nullptr;

	UPROPERTY()
	int32 NotifyCurrentStepIndex = 0;

	UPROPERTY(EditAnywhere)
	ENotifyType NotifyType = ENotifyType::None;

	UFUNCTION()
	virtual void StartNotify();

	UFUNCTION()
	virtual void InitNotifyElement(UQuestData* QuestData, int32 CurrentStepIndex, bool PlayEnterAnim = false);
};
