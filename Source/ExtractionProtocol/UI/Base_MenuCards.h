// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Other/Delegates.h"
#include "Base_MenuCards.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_MenuCards : public UUserWidget
{
	GENERATED_BODY()

public:
    //Button
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (BindWidget))
        class UButton* Button;
    //Text (Info)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (BindWidget))
        class UTextBlock* TitleText;
    //Text (ButtonText)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (BindWidget))
        FText TitleButtonText;
    //Text (InfoText)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (BindWidget))
        class UTextBlock* InfoText;
    //Text (ButtonText)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (BindWidget), meta = (MultiLine = true))
        FText InfoButtonText;
    //Button Clicked sound
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        class USoundBase* ClickSound;
    //Button Hovered sound
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        class USoundBase* HoverSound;
    //Button Hovered Animation
    UPROPERTY(Transient, meta = (BindWidgetAnim))
        class UWidgetAnimation* ScaleAnimation;

    // Event Dispatcher
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
        FEventDispatcher OnButtonClicked;

    float Time;

public:

    virtual void NativePreConstruct();

    virtual void NativeConstruct();

    UFUNCTION()
        void OnClicked();

    UFUNCTION()
        void OnHovered();

    UFUNCTION()
        void OnUnHovered();

    UFUNCTION()
        void ClickTimerDelay();
	
};
