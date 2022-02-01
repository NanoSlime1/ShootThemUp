// Shoot Them Up Game


#include "AI/Decorates/STUNeedAmmoDecorator.h"

#include "AIController.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"

USTUNeedAmmoDecorator::USTUNeedAmmoDecorator()
{
    NodeName = "NeedAmmo";
}

bool USTUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
    if(!WeaponComponent) return false;
    
    return WeaponComponent->NeedAmmo(WeaponType);
}
