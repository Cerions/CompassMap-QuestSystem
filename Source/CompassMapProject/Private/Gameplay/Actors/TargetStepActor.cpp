// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/TargetStepActor.h"
#include "Components/SphereComponent.h"
#include "Gameplay/Interfaces/PlayerInterface.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"

ATargetStepActor::ATargetStepActor()
{
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetGenerateOverlapEvents(true);
	TriggerSphere->SetupAttachment(RootComponent);
}

void ATargetStepActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATargetStepActor::OnStepReached);
}

void ATargetStepActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TriggerSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATargetStepActor::OnStepReached);

	Super::EndPlay(EndPlayReason);
}

void ATargetStepActor::OnStepReached(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<IPlayerInterface>(OtherActor))
	{
		UCMEventManager* EventManager = USingletonFunctionLibrary::GetEventManager(this);
		if (EventManager)
		{
			EventManager->OnStepReachedEvent();
		}
	}
}
