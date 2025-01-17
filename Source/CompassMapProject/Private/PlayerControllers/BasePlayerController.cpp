// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/GameplayGameMode.h"
#include "CompassMapProject/CompassMapProjectCharacter.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"

void ABasePlayerController::BeginPlay()
{
	AGameplayGameMode* GameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->PlayerRef = this;
	}

	Super::BeginPlay();

	SpawnCharacter();
}

void ABasePlayerController::SpawnCharacter()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AGameplayGameMode* GameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(this));
	FTransform CharPosition = FTransform();

	if (GameMode)
	{
		if (CharPosition.GetLocation() == FVector::ZeroVector)
		{
			CharPosition = GameMode->FindPlayerStart(this)->GetActorTransform();
		}
	}

	CharRef = GetWorld()->SpawnActor<ACompassMapProjectCharacter>(PlayerCharacterClass, CharPosition, SpawnInfo);
	Possess(CharRef);

	UCMEventManager* EM = USingletonFunctionLibrary::GetEventManager(GetWorld());
	if (EM)
	{
		EM->OnCharacterRefSetEvent(CharRef);
	}
}
