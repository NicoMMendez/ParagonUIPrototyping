#pragma once

#include "UObject.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "DataTables/FCardData.h"
#include "CardStatModel.h"
#include "CardModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCardModelInUseCountUpdated);

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class DECKBUILDERDESKTOP_API UCardModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		FText CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		FText Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		FText Affinity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		FText Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Card Model")
		TArray<UCardStatModel*> AllStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Card Model")
		TArray<UCardStatModel*> BaseStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Card Model")
		TArray<UCardStatModel*> MaxedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		int32 Count;

public:
	// TODO: Extract
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		int32 InUseCount;

	UPROPERTY(BlueprintAssignable, Category = "Card Model")
		FCardModelInUseCountUpdated OnInUseCountUpdated;

	UFUNCTION(BlueprintCallable, Category = "Card Model")
	void IncrementInUseCount()
	{
		++InUseCount;
		OnInUseCountUpdated.Broadcast();
	}

	UFUNCTION(BlueprintCallable, Category = "Card Model")
	void DecrementInUseCount()
	{
		--InUseCount;
		OnInUseCountUpdated.Broadcast();
	}

public:
	static UCardModel* ConstructFromCardData(const FCardData& CardData, UDataTable* StatDataTable);

	UCardStatModel* GetStatByName(const FString& StatName) const;

	friend bool operator==(const UCardModel& LHS, const UCardModel& RHS);
};
