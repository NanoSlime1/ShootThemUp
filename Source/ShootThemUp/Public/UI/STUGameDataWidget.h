// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "STUGameModeBase.h"
#include "STUPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

class ASTUGameModeBase;
class ASTUPlayerState;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRound() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRoundNum() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundSecondsRemaining() const;
    
private:
    ASTUGameModeBase* GetSTUGameMode() const;
    ASTUPlayerState* GetSTUPlayerState() const;
    
};

	