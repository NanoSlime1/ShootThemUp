// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
        USTUChangeWeaponService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Probability = 0.5;
    
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
