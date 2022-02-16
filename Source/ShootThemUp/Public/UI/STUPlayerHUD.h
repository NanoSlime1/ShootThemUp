// Shoot Them Up Game

#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
public:
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    bool GetGameModeData();
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;
    
	virtual bool Initialize() override;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();
    

private:
    void OnHealthChanged(float Health, float HealthDelta);
    void OnNewPawn(APawn* Pawn);
};



