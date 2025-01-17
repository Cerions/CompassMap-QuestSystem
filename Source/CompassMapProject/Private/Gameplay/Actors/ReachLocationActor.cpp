// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/ReachLocationActor.h"
#include "Components/CapsuleComponent.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"
#include "Gameplay/Components/ObjectStateComponent.h"

#pragma optimize("", off)

AReachLocationActor::AReachLocationActor()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	ObjectStateComp = CreateDefaultSubobject<UObjectStateComponent>(TEXT("ObjectStateComp"));
	CapsuleComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AReachLocationActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (CapsuleComp)
	{
		CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AReachLocationActor::EnterReachLocationArea);
		CapsuleComp->OnComponentEndOverlap.AddDynamic(this, &AReachLocationActor::ExitReachLocationArea);
	}

	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);
	if (EM)
	{
		EM->OnBeginQuestTarget.AddDynamic(this, &AReachLocationActor::HideQuestIcon);
	}

	if (ObjectStateComp)
	{
		ObjectStateComp->ObjectReady();
	}
}

void AReachLocationActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CapsuleComp)
	{
		CapsuleComp->OnComponentBeginOverlap.RemoveDynamic(this, &AReachLocationActor::EnterReachLocationArea);
		CapsuleComp->OnComponentEndOverlap.RemoveDynamic(this, &AReachLocationActor::ExitReachLocationArea);
	}

	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(this);
	if (EM)
	{
		EM->OnBeginQuestTarget.RemoveDynamic(this, &AReachLocationActor::HideQuestIcon);
	}

	Super::EndPlay(EndPlayReason);
}

void AReachLocationActor::EnterReachLocationArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* PlayerPawn = Cast<APawn>(OtherActor);

	if (PlayerPawn)
	{
		OnLocationReached.Broadcast(this);
	}
}

void AReachLocationActor::ExitReachLocationArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* PlayerPawn = Cast<APawn>(OtherActor);

	if (PlayerPawn)
	{
		OnLocationLeave.Broadcast(this);
	}
}

void AReachLocationActor::HideQuestIcon(bool Show, UObjectStateComponent* ObjectStateRef)
{

}

