// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AI/EnemyAIController.h"
#include "Gameplay/Characters/BaseEnemy.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Gameplay/Characters/CMPlayer.h"
#include "Gameplay/AI/BlackboardKeyManager.h"

void AEnemyAIController::SetSightValues()
{
	FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());

	auto Config = GetPerceptionComponent()->GetSenseConfig(Id);

	if (Config)
	{
		auto ConfigSight = Cast<UAISenseConfig_Sight>(Config);
		if (ConfigSight)
		{
			float LoseRange = ConfigSight->LoseSightRadius - ConfigSight->SightRadius;
			if (Enemy)
			{
				//ConfigSight->SightRadius = Enemy->WarningConeDistance;
				ConfigSight->LoseSightRadius = ConfigSight->SightRadius + LoseRange;
				ConfigSight->PeripheralVisionAngleDegrees = Enemy->PeripheralVision;
				GetPerceptionComponent()->RequestStimuliListenerUpdate();
			}
		}
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	UAIPerceptionComponent* PerceptionComp = GetPerceptionComponent();
	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::PerceptionUpdated);
	}
}

void AEnemyAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UAIPerceptionComponent* PerceptionComp = GetPerceptionComponent();
	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.RemoveDynamic(this, &AEnemyAIController::PerceptionUpdated);
	}
	Super::EndPlay(EndPlayReason);
}

void AEnemyAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	ACMPlayer* Player = Cast<ACMPlayer>(Actor);
	if (Player)
	{
		bool bIsEngaged = GetValueAsBool(UBlackboardKeyManager::IsEngagedKey);
		if (Stimulus.WasSuccessfullySensed())
		{
			SetValueAsBool(UBlackboardKeyManager::CanSeePlayerKey, true);
			if (!bIsEngaged)
			{
				if (Enemy)
				{
					// Make enemy move towards the player
				}
			}
		}
		else
		{
			SetValueAsBool(UBlackboardKeyManager::CanSeePlayerKey, false);
			if (!bIsEngaged)
			{
				if (Enemy)
				{
					// Make enemy patrol again
				}
			}
		}
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Enemy = Cast<ABaseEnemy>(GetPawn());
}
