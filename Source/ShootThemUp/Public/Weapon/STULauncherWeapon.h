// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTURocket;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
public:
    virtual void StartFire() override;
    virtual void StopFire() override;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTURocket> ProjectileClass;
    
    virtual void MakeShot() override;

private:
    FTimerHandle ShotTimerHandle;
    

	
};
