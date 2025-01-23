// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AI/PatrolTrack.h"
#include "Components/SplineComponent.h"

APatrolTrack::APatrolTrack()
{
    SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
    SplineComp->SetupAttachment(RootComponent);

}

