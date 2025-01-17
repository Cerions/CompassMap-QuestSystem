// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CompassMap.h"
#include "Gameplay/Interfaces/PlayerInterface.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Camera/CameraComponent.h"
#include "Components/CanvasPanel.h"
#include "UI/CompassIcon.h"
#include "FunctionLibraries/GameplayFunctionLibrary.h"
#include "Managers/MapManager.h"
#include "FunctionLibraries/SingletonFunctionLibrary.h"
#include "Managers/CMEventManager.h"

void UCompassMap::NativeConstruct()
{
	Super::NativeConstruct();

	//GameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(this));

	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(MarkerContainer);
	if (PanelSlot)
	{
		UCanvasPanelSlot* ImageSlot = Cast<UCanvasPanelSlot>(CompassImage);
		if (ImageSlot)
		{
			FVector2D CompassImageSize = ImageSlot->GetSize();
			PanelSlot->SetSize(FVector2D(CompassImageSize.X, CompassImageSize.Y));
		}
	}

	UCMEventManager* EventManager = USingletonFunctionLibrary::GetEventManager(this);

	if (EventManager)
	{
		EventManager->OnPOIsActivated.AddUniqueDynamic(this, &UCompassMap::OnPOIsActivated);
		/*EventManager->OnPOIEnter.AddDynamic(this, &UCompassMap::UpdatePOIs);*/
		EventManager->OnMarkerNotify.AddDynamic(this, &UCompassMap::UpdateMarkers);
		/*EventManager->OnQuestAreaEnter.AddUniqueDynamic(this, &UCompassMap::OnQuestAreaEnter);
		EventManager->OnQuestAreaLeave.AddUniqueDynamic(this, &UCompassMap::OnQuestAreaLeave);*/
	}
}

void UCompassMap::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Progress += InDeltaTime;
	if (Progress >= TickValue)
	{
		UpdateCompassDirection();
		UpdateMarkerPosition();
	}
}

void UCompassMap::NativeDestruct()
{
	UCMEventManager* EventManager = USingletonFunctionLibrary::GetEventManager(this);

	if (EventManager)
	{
		EventManager->OnPOIsActivated.RemoveDynamic(this, &UCompassMap::OnPOIsActivated);
		/*EventManager->OnPOIEnter.RemoveDynamic(this, &UCompassMap::UpdatePOIs);*/
		EventManager->OnMarkerNotify.RemoveDynamic(this, &UCompassMap::UpdateMarkers);
		/*EventManager->OnQuestAreaEnter.RemoveDynamic(this, &UCompassMap::OnQuestAreaEnter);
		EventManager->OnQuestAreaLeave.RemoveDynamic(this, &UCompassMap::OnQuestAreaLeave);*/
	}

	Super::NativeDestruct();
}

void UCompassMap::UpdateCompassDirection()
{
	if (PlayerInterface)
	{
		FVector VectorPlane = FVector::VectorPlaneProject(PlayerInterface->GetActiveCamera()->GetForwardVector(), FVector::UpVector);
		VectorPlane.Normalize();
		double DotProduct = FVector::DotProduct(-FVector::RightVector, VectorPlane);
		double acos = acosf(DotProduct);

		float AngleVectors = FMath::RadiansToDegrees(acos);
		AngleVectors *= (VectorPlane.X == 0 ? 1 : FMath::Sign(VectorPlane.X));
		NorthCompassOffset = (AngleVectors / 180) * DistanceBetweenCardinalPoint;

		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(CompassImage->Slot);
		if (CanvasPanelSlot)
		{
			CanvasPanelSlot->SetPosition(FVector2D(-NorthCompassOffset, 0.0f));
		}
	}
}

void UCompassMap::UpdateMarkerPosition()
{
	if (OwnerWidget)
	{
		if (MapManager)
		{
			TArray<FMarkerPosition> DynamicsMarkers = MapManager->GetDynamicMarkers();

			for (UCompassIcon* Icon : CompassIcons)
			{
				if (Icon->MarkerData.bIsDynamic)
				{
					for (FMarkerPosition Marker : DynamicsMarkers)
					{
						if (Marker.ObjectID == Icon->MarkerData.Id)
						{
							Icon->MarkerData.Location = Marker.Location;
							break;
						}
					}
				}

				float XPos = GetScreenLocation(Icon->MarkerData.Location);
				if (Icon->MarkerData.IconInfo && Icon->MarkerData.IconInfo->bSnaptoCompassBounds)
				{
					float CompassCanvasSize = Cast<UCanvasPanelSlot>(CompassCanvas->Slot)->GetSize().X;
					float v1 = Cast<UCanvasPanelSlot>(ClampCanvas->Slot)->GetOffsets().Left - CompassCanvasSize / 2;
					float v2 = CompassCanvasSize / 2 - Cast<UCanvasPanelSlot>(ClampCanvas->Slot)->GetOffsets().Right;
					XPos = FMath::Clamp(XPos, v1, v2);
				}

				Icon->SetRenderTranslation(FVector2D(XPos, 0.0f));
				Icon->UpdateMarker();
			}

			for (UCompassIcon* IconToCheck : CompassIcons)
			{
				if (!IconToCheck->IsVisible()) continue;
				bool bHideIconToCheck = false;
				for (UCompassIcon* IconToComparison : CompassIcons)
				{
					if (IconToCheck == IconToComparison || (!IconToComparison->IsVisible())) continue;

					float Diff = IconToCheck->GetRenderTransform().Translation.X - IconToComparison->GetRenderTransform().Translation.X;
					if (abs(Diff) <= OverlapDifferenceValue)
					{
						if (IconToCheck->GetIconZOrder() == IconToComparison->GetIconZOrder())
						{
							bHideIconToCheck = IconToCheck->GetDistanceFromPlayer() >= IconToComparison->GetDistanceFromPlayer();
						}
						else
						{
							bHideIconToCheck = IconToCheck->GetIconZOrder() < IconToComparison->GetIconZOrder();
						}
						IconToComparison->DisableDistanceText(!bHideIconToCheck);
					}
				}
				IconToCheck->DisableDistanceText(bHideIconToCheck);
			}
		}
	}
}

float UCompassMap::GetScreenLocation(FVector TargetLocation)
{
	if (PlayerInterface && OwnerWidget)
	{
		FVector Distance = TargetLocation - OwnerWidget->GetActorLocation();
		Distance.Normalize();

		FVector VectorPlane = FVector::VectorPlaneProject(Distance, FVector::UpVector);
		VectorPlane.Normalize();
		
		FVector ForwardCamera = FVector::VectorPlaneProject(PlayerInterface->GetActiveCamera()->GetForwardVector(), FVector::UpVector);
		ForwardCamera.Normalize();

		double DotProduct = FVector::DotProduct(ForwardCamera, VectorPlane);

		double acos = acosf(DotProduct);
		float AngleVectors = FMath::RadiansToDegrees(acos);
		
		float Dir = FMath::Sign(FVector::CrossProduct(ForwardCamera, VectorPlane) | FVector::UpVector);

		AngleVectors = Dir * (AngleVectors / 180) * DistanceBetweenCardinalPoint;

		return AngleVectors;
	}

	return 0.f;
}

void UCompassMap::OnPOIsActivated()
{
	MapManager = UGameplayFunctionLibrary::GetMapManagerActor(GetWorld());
	if (MapManager)
	{
		TArray<FPOIConfigRow> POIs{};
		MapManager->GetAllPOI(POIs);
		for (FPOIConfigRow POI : POIs)
		{
			CreateMarker(POI);
		}
	}
}

void UCompassMap::UpdatePOIs(const FPOIConfigRow& POI, bool NewDiscovery)
{
	if (POI.IconInfo && POI.IconInfo->MarkerType != EMarkerType::OnlyMap)
	{
		CreateMarker(POI);
	}
}

void UCompassMap::UpdateMarkers(const FPOIConfigRow& Row, bool Add)
{
	if (Add)
	{
		if (Row.IconInfo && Row.IconInfo->MarkerType != EMarkerType::OnlyMap)
		{
			CreateMarker(Row);
		}
	}
	else
	{
		RemoveMarker(Row);
	}
}

void UCompassMap::CreateMarker(const FPOIConfigRow& Row)
{
	bool Create = true;
	if (OwnerWidget && (Row.IconInfo->MarkerType != EMarkerType::OnlyMap))
	{
		if (Create)
		{
			UCompassIcon* CompassIconRef = CreateWidget<UCompassIcon>(GetWorld(), CompassIconClass);
			if (CompassIconRef)
			{
				MapManager = UGameplayFunctionLibrary::GetMapManagerActor(GetWorld());
				if (MapManager)
				{
					CompassIconRef->SetupWidget(OwnerWidget, Row, MapManager->GetPOILocation(Row.Id));
					HiddenPOI.Contains(CompassIconRef->MarkerData.Id) ? CompassIconRef->SetRenderOpacity(0.f) : CompassIconRef->SetRenderOpacity(1.f);
					CompassIcons.Add(CompassIconRef);
					UPanelSlot* PanelSlot = MarkerContainer->AddChild(CompassIconRef);
					if (PanelSlot)
					{
						UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot);
						if (CanvasSlot)
						{
							FVector2D MiddleVector2d = FVector2D(.5f, .5f);
							CanvasSlot->SetAlignment(MiddleVector2d);
							FAnchors Anchors = FAnchors();
							Anchors.Maximum = MiddleVector2d;
							Anchors.Minimum = MiddleVector2d;
							CanvasSlot->SetAnchors(Anchors);
							CanvasSlot->SetZOrder(Row.IconInfo->IconCompassZOrder);
							UCanvasPanelSlot* ContainerSlot = Cast<UCanvasPanelSlot>(MarkerContainer->Slot);
							if (ContainerSlot)
							{
								FVector2D ContainerSize = ContainerSlot->GetSize();
								CanvasSlot->SetSize(FVector2D(ContainerSize.Y, ContainerSize.Y));
							}
						}
					}					
				}
			}			
		}
	}
}

void UCompassMap::RemoveMarker(const FPOIConfigRow& Row)
{
	UCompassIcon* IconToRemove = nullptr;
	for (UCompassIcon* Icon : CompassIcons)
	{
		if (Icon->MarkerData.Id == Row.Id)
		{
			IconToRemove = Icon;
			break;
		}
	}

	if (IconToRemove)
	{
		IconToRemove->RemoveFromParent();
		CompassIcons.Remove(IconToRemove);
	}
}

void UCompassMap::HidePOI(FName POIID, bool bHide)
{
	HiddenPOI.Empty();

	for (UCompassIcon* Icon : CompassIcons)
	{
		if (Icon->MarkerData.Id == POIID)
		{
			if (bHide)
			{
				Icon->SetRenderOpacity(0.f);
				HiddenPOI.Add(POIID);
			}
			else
			{
				Icon->SetRenderOpacity(1.f);
				if (HiddenPOI.Contains(POIID))
				{
					HiddenPOI.Remove(POIID);
				}
			}
		}
	}
}

void UCompassMap::OnQuestAreaEnter(FName QuestAreaID)
{

}

void UCompassMap::OnQuestAreaLeave(FName QuestAreaID)
{

}

void UCompassMap::InitWidget(AActor* WidgetOwner)
{
	if (WidgetOwner)
	{
		OwnerWidget = WidgetOwner;
		PlayerInterface = Cast<IPlayerInterface>(OwnerWidget);
	}

	for (UCompassIcon* Icon : CompassIcons)
	{
		Icon->RemoveFromParent();
	}

	CompassIcons.Empty();

	MapManager = UGameplayFunctionLibrary::GetMapManagerActor(GetWorld());
	if (MapManager)
	{
		TArray<FPOIConfigRow> POIs{};
		MapManager->GetAllPOI(POIs);
		for (FPOIConfigRow POI : POIs)
		{
			CreateMarker(POI);
		}
	}

	//// Check if we are inside a QuestArea
	//bool bInsideQuestArea = false;
	//if (GameMode && GameMode->UIHelper)
	//{
	//	for (UCompassIcon* Icon : CompassIcons)
	//	{
	//		if (Icon->MarkerData.Id == GameMode->UIHelper->LastQuestAreaID)
	//		{
	//			if (GameMode->UIHelper->bEnteredQuestArea)
	//			{
	//				bInsideQuestArea = true;
	//				HidePOI(GameMode->UIHelper->LastQuestAreaID, true);
	//				QuestAreaIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
	//			}
	//		}
	//	}
	//}
	//if (!bInsideQuestArea)
	//{
	//	GameMode->UIHelper->bEnteredQuestArea = false;
	//}
}
