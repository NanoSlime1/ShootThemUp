// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "STUPauseWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPauseWidget : public USTUBaseWidget
{
    GENERATED_BODY()
    
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnClearPause();
};
