// Shoot Them Up Game


#include "Weapon/Components/STUWeaponFXComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


USTUWeaponFXComponent::USTUWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult &Hit)
{
    auto ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),                   //
                                                   ImpactData.NiagaraEffect,     //
                                                   Hit.ImpactPoint,              //
                                                   Hit.ImpactNormal.Rotation()); //

    auto DecaleComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),                    //
                                                                  ImpactData.DecalData.Material, //
                                                                  ImpactData.DecalData.Size,     //
                                                                  Hit.ImpactPoint,               //
                                                                  Hit.ImpactNormal.Rotation());

    if (DecaleComponent)
    {
        DecaleComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.ImpactSound, Hit.ImpactPoint);
}
