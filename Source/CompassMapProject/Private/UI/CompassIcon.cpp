// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CompassIcon.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FunctionLibraries/GameplayFunctionLibrary.h"
#include "Structures/GameplayConstants.h"

void UCompassIcon::SetupWidget(AActor* ActorRef, const FPOIConfigRow& Row, const FVector& POILocation)
{
	TargetActor = ActorRef;
	MarkerData = Row;
	MarkerData.Location = POILocation;
	IconZOrder = Row.IconInfo->IconCompassZOrder;

	if (Row.IconInfo && Row.IconInfo->Icon.ToSoftObjectPath().IsValid())
	{
		IconImage->SetBrushFromTexture(Row.IconInfo->Icon.LoadSynchronous());
	}
	UpdateMarker();
}

void UCompassIcon::UpdateMarker()
{
	if (TargetActor && MarkerData.IconInfo)
	{
		Distance = FVector::Dist(TargetActor->GetActorLocation(), MarkerData.Location);

		if ((MarkerData.IconInfo->bAlwaysVisible || Distance < MarkerData.IconInfo->DistanceFromPlayerToBecomeVisible))
		{
			DistanceFromPlayer->SetText(FText::FromString(FString::FromInt(Distance / 100)));
			SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			UGameplayConstants* GC = UGameplayFunctionLibrary::GetGameplayConstants(this);
			if (GC)
			{
				float DistanceZ = TargetActor->GetActorLocation().Z - MarkerData.Location.Z;
				if (DistanceZ > GC->MinMaxCompassIconArrowDistanceZ.X && DistanceZ < GC->MinMaxCompassIconArrowDistanceZ.Y)
				{
					ArrowImage->SetVisibility(ESlateVisibility::Collapsed);
				}
				else
				{
					ArrowImage->SetVisibility(ESlateVisibility::Visible);
					if (TargetActor->GetActorLocation().Z < MarkerData.Location.Z)
					{
						ArrowImage->SetRenderTransformAngle(0.f);
					}
					else
					{
						ArrowImage->SetRenderTransformAngle(180.f);
					}
				}
			}
		}
		else
		{
			SetVisibility(ESlateVisibility::Hidden);
		}

	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

const int32 UCompassIcon::GetIconZOrder()
{
	return IconZOrder;
}

void UCompassIcon::DisableDistanceText(bool Disable)
{
	DistanceFromPlayerContainer->SetVisibility(Disable ? ESlateVisibility::Hidden : ESlateVisibility::HitTestInvisible);
	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Slot);
	if (PanelSlot)
	{
		return PanelSlot->SetZOrder(Disable ? -1 : IconZOrder);
	}
}