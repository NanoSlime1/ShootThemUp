// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "NiagaraComponent.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()
	
public:	
    ASTUBaseWeapon();
    
    FOnClipEmptySignature OnClipEmpty;
    
    virtual void StartFire();
    virtual void StopFire();
    bool IsFiring() const;

    void ChangeClip();
    bool CanReload() const;

    FWeaponUIData GetUIData() const { return UIData;};
    FAmmoData GetCurrentAmmoData() const { return CurrentAmmo;};

    bool TryToAddAmmo(int32 ClipsAmount);
    
    bool IsAmmoFull() const;
    bool IsAmmoEmpty() const;

    virtual void Zoom(bool Enable) {};

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponSkeletonMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleFlashSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* MuzzleFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* FireSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* NoAmmoSound;
    
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    
    void MakeHit(FHitResult &HitResult, FVector &TraceStart, FVector &TraceEnd) const;
    
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    virtual void MakeShot();
	virtual void BeginPlay() override;

    void DecreaseAmmo();
    bool IsClipEmpty() const;

    bool FireInProgress = false;

    void LogAmmo();

    UNiagaraComponent* SpawnMuzzleFX();

private:
    FAmmoData CurrentAmmo;
	
	

};
