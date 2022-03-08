// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UAudioComponent;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
public:
    ASTURifleWeapon();
    
    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void Zoom(bool Enable) override;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    float BulletSpread = 1.5f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    USTUWeaponFXComponent* WeaponFXComponent;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float FOVZoomAngle = 50.0f;
    
    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override;



private:
    FTimerHandle ShotTimerHandle;
    
    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UNiagaraComponent* MuzzleFXComponent;
    
    UPROPERTY()
    UAudioComponent* FireAudioComponent;
    
    void MakeDamage(const FHitResult &HitResult);
    void InitFX();
	void SetMuzzleFXActive(bool IsActive);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

    AController* GetController() const;

    float DefaultCameraFOV = 90.0f;
};
