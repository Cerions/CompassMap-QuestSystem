// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/TargetBaseActor.h"
#include "Gameplay/Components/ObjectStateComponent.h"

ATargetBaseActor::ATargetBaseActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComp->SetGenerateOverlapEvents(false);
	StaticMeshComp->SetupAttachment(RootComponent);
	ObjectStateComp = CreateDefaultSubobject<UObjectStateComponent>(TEXT("ObjectStateComponent"));
	ObjectStateComp->SetCanEverAffectNavigation(false);
}

void ATargetBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (ObjectStateComp)
	{
		ObjectStateComp->ObjectReady();
	}
}

