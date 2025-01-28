// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestNotifyContainer.generated.h"

/**
 * 
 */
UCLASS()
class COMPASSMAPPROJECT_API UQuestNotifyContainer : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* FixedElementContainer {};

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* NotifyElementContainer {};

	UPROPERTY()
	UQuestNotifyElement* ActualNotifyElement {};

	UPROPERTY()
	UQuestNotifyElement* ActualFixedNotifyElement {};

	UPROPERTY()
	FTimerHandle TimerCheckForPrint;

	UPROPERTY()
	bool bPauseNotify = false;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void CheckNotifyToPrint();

	UFUNCTION()
	void RemoveNotify(UQuestNotifyElement* NotifyElement);

	UFUNCTION()
	void RemoveFixedNotify(UQuestNotifyElement* NotifyElement);

	UFUNCTION()
	void ClearPendingQuestNotify();

public:

	UFUNCTION()
	void Init();

};
