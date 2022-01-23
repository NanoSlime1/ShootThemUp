// Shoot Them Up Game


#include "STURocket.h"

#include "DrawDebugHelpers.h"
#include "STUWeaponFXComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASTURocket::ASTURocket()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    ProjectileMovementComponent->InitialSpeed = 1500.0f;

    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURocket::BeginPlay()
{
    Super::BeginPlay();

    check(ProjectileMovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTURocket::OnProjectileHit);
    SetLifeSpan(LifeSecond);
}

void ASTURocket::OnProjectileHit(
    UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse,
    const FHitResult &Hit)
{
    if (!GetWorld()) return;

    ProjectileMovementComponent->StopMovementImmediately();
    
    //make damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(),                 //
                                        DamageAmount,               //
                                        GetActorLocation(),         //
                                        DamageRadius,               //
                                        UDamageType::StaticClass(), //
                                        {GetOwner()},             //
                                        this,                       //
                                        GetController(),            //
                                        DoFullDamage);
    
    WeaponFXComponent->PlayImpactFX(Hit);
    Destroy();
}

AController* ASTURocket::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}


