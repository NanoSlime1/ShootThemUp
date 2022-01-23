// Shoot Them Up Game


#include "Pickups/STUHealthPickup.h"

#include "STUHealthComponent.h"
#include "STUUtils.h"



bool ASTUHealthPickup::GivePickupTo(APawn *PlayerPawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if(!HealthComponent || HealthComponent->IsDead()) return false;
    
    return HealthComponent->TryToAddHealth(Heal);
}
