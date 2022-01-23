// Shoot Them Up Game


#include "AI/Tasks/STUNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUNextLocationTask::USTUNextLocationTask()
{
    NodeName = "Next Location";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    if(!Controller || !BlackBoard) return EBTNodeResult::Failed;

    const auto Pawn = Controller->GetPawn();
    if(!Pawn) return EBTNodeResult::Failed;;

    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if(!NavSys) return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    auto Location = Pawn->GetActorLocation();
    if(!SelfCenter)
    {
        const auto CenterActor = Cast<AActor>(BlackBoard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if(!CenterActor) return EBTNodeResult::Failed;
        
        Location = CenterActor->GetActorLocation(); 
    }
    
    const auto Found = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
    if(!Found) return EBTNodeResult::Failed;

    BlackBoard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
    
    return EBTNodeResult::Succeeded;
}
