// Shoot Them Up Game


#include "Pickups/STUAmmoPickup.h"

#include "STUHealthComponent.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"

bool ASTUAmmoPickup::GivePickupTo(APawn *PlayerPawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if(!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;  
    
    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
