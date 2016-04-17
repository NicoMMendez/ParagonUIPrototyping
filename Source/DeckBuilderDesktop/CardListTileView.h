// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TableViewBase.h"
#include "CardListTileView.generated.h"

/**
 * Duplicated from UTileView, removed the Experimental tag.
 */
UCLASS()
class DECKBUILDERDESKTOP_API UCardListTileView : public UTableViewBase
{
	GENERATED_UCLASS_BODY()

public:

	/**  */
	UPROPERTY(EditAnywhere, Category = Appearance)
		float ItemWidth;

	/**  */
	UPROPERTY(EditAnywhere, Category = Appearance)
		float ItemHeight;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
		TArray<UObject*> Items;

	/**  */
	UPROPERTY(EditAnywhere, Category = Content)
		TEnumAsByte<ESelectionMode::Type> SelectionMode;

	/**  */
	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
		FOnGenerateRowUObject OnGenerateTileEvent;

public:

	/** Set item width */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetItemWidth(float Width);

	/** Set item height */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetItemHeight(float Height);

	/** Refreshes the list */
	UFUNCTION(BlueprintCallable, Category = "Behavior")
		void RequestListRefresh();

	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface

#if WITH_EDITOR
	virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	TSharedRef<ITableRow> HandleOnGenerateTile(UObject* Item, const TSharedRef< STableViewBase >& OwnerTable) const;

	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

protected:
	TSharedPtr< STileView< UObject* > > MyTileView;
};
