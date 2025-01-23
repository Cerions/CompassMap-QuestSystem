// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Characters/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Gameplay/Components/ObjectStateComponent.h"
#include "Gameplay/AI/EnemyAIController.h"
#include "Gameplay/AI/BlackboardKeyManager.h"
#include "FunctionLibraries/GameplayFunctionLibrary.h"
#include "Gameplay/Characters/CMPlayer.h"
#include "Components/SplineComponent.h"
#include "Gameplay/AI/PatrolTrack.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	ObjectStateComp = CreateDefaultSubobject<UObjectStateComponent>(TEXT("ObjectStateComponent"));
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	AEnemyAIController* EnemyAIController = GetAIController();
	if (EnemyAIController)
	{
		EnemyAIController->OnAIControllerLoadedDelegate.AddUniqueDynamic(this, &ABaseEnemy::OnAIControllerLoaded);
	}
	
}

AActor* ABaseEnemy::GetTarget()
{
	return UGameplayStatics::GetPlayerPawn(this, 0);
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AEnemyAIController* ABaseEnemy::GetAIController() const
{
	return Cast<AEnemyAIController>(GetController());
}

void ABaseEnemy::OnHit()
{
	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnEnemyDeathEvent(this);
	}
	Destroy();
}

void ABaseEnemy::OnAIControllerLoaded()
{
	AEnemyAIController* EnemyAIController = GetAIController();
	if (EnemyAIController)
	{
		EnemyAIController->OnAIControllerLoadedDelegate.RemoveDynamic(this, &ABaseEnemy::OnAIControllerLoaded);

		EnemyAIController->SetSightValues();
		EnemyAIController->SetValueAsVector(UBlackboardKeyManager::StartingForwardKey, StartingPosition + GetActorForwardVector() * 1000.f);
		EnemyAIController->SetValueAsObject(UBlackboardKeyManager::TargetKey, UGameplayFunctionLibrary::GetPlayerCharacter(this));
	}

	/*TArray<AActor*> Splines;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APatrolTrack::StaticClass(), Splines);
	for (AActor* Spline : Splines)
	{
		APatrolTrack* Track = Cast<APatrolTrack>(Spline);
		if (Track)
		{
			if (Track->TrackID == TrackID)
			{
				Track->EnemiesOnTrack.Add(this);
				CurrentSpline = Track->FindComponentByClass<USplineComponent>();
				if (CurrentSpline)
				{
					ClosestPointOnSpline = CurrentSpline->FindLocationClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
					DistanceOnSpline = (CurrentSpline->FindInputKeyClosestToWorldLocation(GetActorLocation()) / (CurrentSpline->GetNumberOfSplinePoints() - 1)) * CurrentSpline->GetSplineLength();
				}
			}
		}
	}*/

	if (ObjectStateComp)
	{
		ObjectStateComp->ObjectReady();
	}
}

