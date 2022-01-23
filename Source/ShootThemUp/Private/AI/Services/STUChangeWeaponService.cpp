// Shoot Them Up Game


#include "AI/Services/STUChangeWeaponService.h"

#include "AIController.h"
#include "STUAIWeaponComponent.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "ChangeWeapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(Controller)
    {
        const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
        if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
