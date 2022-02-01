// Shoot Them Up Game


#include "AI/EQS/STUEnemyEnvQueryContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

    const auto BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
    if(!BlackBoard) return;
    
    const auto ContextActor = BlackBoard->GetValueAsObject(EnemyActorKey);
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
}
