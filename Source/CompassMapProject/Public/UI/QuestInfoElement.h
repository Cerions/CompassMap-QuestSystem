// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/QuestNotifyElement.h"
#include "QuestInfoElement.generated.h"

class UTextBlock;
class UQuestData;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UQuestInfoElement : public UQuestNotifyElement
{
	GENERATED_BODY()

protected:

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* OpenAnimation;

	FWidgetAnimationDynamicEvent CloseAnimationFinished;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestName {};

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestStepDescription {};

	void NativeConstruct() override;
	void NativeDestruct() override;

	UFUNCTION()
	void RemoveWidget(const FName& QuestID, const int32 CurrentStepIndex);

	UFUNCTION()
	void ManageCloseAnimationFinished();

public:

	void InitNotifyElement(UQuestData* QuestData, int32 CurrentStepIndex, bool PlayEnterAnimation = false) override;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* CloseAnimation {};

	void StartNotify() override;

};
