// Shoot Them Up Game


#include "AI/Decorates/STUHealthPercentDecorator.h"

#include "AIController.h"
#include "STUHealthComponent.h"
#include "STUUtils.h"

USTUHealthPercentDecorator::USTUHealthPercentDecorator()
{
    NodeName = "HealthPercent";
}

bool USTUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Controller->GetPawn());
    if(!HealthComponent || HealthComponent->IsDead()) return false;
    
    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
