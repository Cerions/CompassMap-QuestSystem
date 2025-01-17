// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayStructures.generated.h"

class UStepBase;
class UObjectStateComponent;

/**
 * 
 */
UENUM(BlueprintType)
enum class EMarkerType : uint8
{
	MapAndCompass = 0,
	OnlyCompass = 1,
	OnlyMap = 2
};

UENUM(BlueprintType)
enum class ENotifyType : uint8
{
	None = 0,
	StartQuest = 1,
	EndQuest = 2,
	StartStep = 3,
	EndStep = 4
};

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	Starting = 0,
	StepEnd = 1,
	StepStart = 2,
	Ending = 3,
	Complete = 4
};

USTRUCT(BlueprintType)
struct COMPASSMAPPROJECT_API FMarkerPosition
{
	GENERATED_USTRUCT_BODY()

public:

	FMarkerPosition()
	{
		Location = FVector();
	}

	FMarkerPosition(FName _ObjectID, FName _Type, FVector _Location, float _AreaSize = 0.f)
	{
		ObjectID = _ObjectID;
		Type = _Type;
		Location = _Location;
		AreaSize = _AreaSize;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
	FName ObjectID {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
	FName Type {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
	FVector Location = FVector();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
	float AreaSize = 0.f;

	bool operator==(const FMarkerPosition& Other) const
	{
		return ObjectID == Other.ObjectID;
	}
};

USTRUCT(BlueprintType)
struct COMPASSMAPPROJECT_API FPOIConfigRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FPOIConfigRow()
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
	FName Id {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
	FText Name {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
	FText Description {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
	bool bIsDynamic = false;

	UPROPERTY(/*EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "bIsDynamic == false", EditConditionHides)*/)
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
	UPOIIcon* IconInfo {};

	UPROPERTY()
	FVector2D MapPosition = FVector2D::ZeroVector;

	UPROPERTY()
	float AreaSize = 0.f;

	bool operator==(const FPOIConfigRow& Other) const
	{
		return Id == Other.Id;
	}
};

UCLASS()
class COMPASSMAPPROJECT_API UPOIIcon : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
		TSoftObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN")
		EMarkerType MarkerType = EMarkerType::MapAndCompass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "MarkerType != EMarkerType::OnlyMap", EditConditionHides))
		bool bAlwaysVisible = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "bAlwaysVisible == false || MarkerType != EMarkerType::OnlyMap", EditConditionHides))
		float DistanceFromPlayerToBecomeVisible = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "MarkerType != EMarkerType::OnlyMap", EditConditionHides))
		bool bSnaptoCompassBounds = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "MarkerType != EMarkerType::OnlyMap", EditConditionHides))
		int32 IconCompassZOrder = 0;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "MarkerType != EMarkerType::OnlyCompass", EditConditionHides))
		TSubclassOf<UBaseMapElement> MapIconClass;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "MarkerType != EMarkerType::OnlyCompass", EditConditionHides))
		int32 ZOrderMap = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "MarkerType != EMarkerType::OnlyCompass", EditConditionHides))
		FVector2D ZoomRangeVisibilityMap = FVector2D(0.25f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "MarkerType != EMarkerType::OnlyCompass", EditConditionHides))
		bool bShowPinInfoInMap = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "bIsCurrenQuestPOI == false", EditConditionHides))
		bool bIsFastTravelPOI = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESIGN", meta = (EditCondition = "bIsFastTravelPOI == false", EditConditionHides))
		bool bIsCurrentQuestPOI = false;
};

// QUESTS
UCLASS()
class COMPASSMAPPROJECT_API UQuestData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FName QuestID = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UStepBase*> Steps = {};
};

USTRUCT(BlueprintType)
struct COMPASSMAPPROJECT_API FQuestTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UQuestData* QuestData {};
};

USTRUCT(BlueprintType)
struct COMPASSMAPPROJECT_API FQuestInfo
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FName QuestID = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	int32 StepID = 0;
};

USTRUCT(BlueprintType)
struct COMPASSMAPPROJECT_API FObjectStateWorldRef
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	UObjectStateComponent* SpawnedObject {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FTransform StoredPosition {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	float StoredExtension {};
};

USTRUCT(BlueprintType)
struct COMPASSMAPPROJECT_API FQuestActorTransformDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(EditAnywhere)
	FTransform ObjectTransform;

	UPROPERTY(EditAnywhere)
	float AreaSize = 0.f;
};