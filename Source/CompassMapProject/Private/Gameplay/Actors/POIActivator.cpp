// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/POIActivator.h"
#include "Components/SphereComponent.h"
#include "FunctionLibraries/GameplayFunctionLibrary.h"
#include "Gameplay/Interfaces/PlayerInterface.h"
//#include "Gameplay/Actors/TargetStaticActor.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"
#include "Gameplay/Actors/ReachLocationActor.h"
#include "Gameplay/Components/ObjectStateComponent.h"

APOIActivator::APOIActivator()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetGenerateOverlapEvents(true);
	TriggerSphere->SetupAttachment(RootComponent);
}

void APOIActivator::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &APOIActivator::OnPOIActivatorOverlap);
}

void APOIActivator::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TriggerSphere->OnComponentBeginOverlap.RemoveDynamic(this, &APOIActivator::OnPOIActivatorOverlap);

	Super::EndPlay(EndPlayReason);
}

void APOIActivator::OnPOIActivatorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<IPlayerInterface>(OtherActor))
	{
		for (AReachLocationActor* ReachLocationActor : ReachLocationActors)
		{
			if (ReachLocationActor->ObjectStateComp)
			{
				ReachLocationActor->ObjectStateComp->ObjectReady();
				UGameplayFunctionLibrary::AddPOI(ReachLocationActor->ObjectStateComp->ObjectID, ReachLocationActor->GetActorLocation(), GetWorld());
			}			
		}

		UCMEventManager* EventManager = USingletonFunctionLibrary::GetEventManager(this);
		if (EventManager)
		{
			//EventManager->OnPOIsActivatedEvent();
		}
	}
}

