// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USoundCue;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBasePickup();


protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* TakenSound;
    
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
    
    bool CouldBeTaken() const;
    
private:
    FTimerHandle RespawnTimerHandle;
    
    float RotationYaw = 0.0f;

    UPROPERTY()
    TArray<APawn*> OverlappingPawns;
    
    virtual bool GivePickupTo(APawn* PlayerPawn);
    
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
