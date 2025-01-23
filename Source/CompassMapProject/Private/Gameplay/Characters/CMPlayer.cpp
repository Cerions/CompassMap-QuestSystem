// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Characters/CMPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Gameplay/Interfaces/EnemyInterface.h"

UCameraComponent* ACMPlayer::GetActiveCamera()
{
	return GetFollowCamera();
}

void ACMPlayer::SphereAttack()
{
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 100;
	FName CollisionProfileName;
	TArray<FHitResult> OutHits;
	TArray<AActor*> ActorsToIgnore;

	UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), Start, End, SphereRadius, CollisionProfileName, false,
		ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHits, true, FLinearColor::Red, FLinearColor::Green, 2.f);

	for (FHitResult OutHit : OutHits)
	{
		if (Cast<IEnemyInterface>(OutHit.GetActor()))
		{
			Cast<IEnemyInterface>(OutHit.GetActor())->OnHit();
		}
	}
}
