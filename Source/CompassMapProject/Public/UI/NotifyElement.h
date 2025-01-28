// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/QuestNotifyElement.h"
#include "NotifyElement.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UNotifyElement : public UQuestNotifyElement
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestName;

	void InitNotifyElement(UQuestData* QuestData, int32 CurrentStepIndex, bool PlayEnterAnimation = false) override;

	UFUNCTION(BlueprintCallable)
	void SetIsPendingClose(bool PendingClose) { bIsPendingClose = PendingClose; };

};
