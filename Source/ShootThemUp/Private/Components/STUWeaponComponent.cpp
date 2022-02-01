// Shoot Them Up Game


#include "Components/STUWeaponComponent.h"
#include "STUBaseWeapon.h"
#include "STUReloadFinishedAnimNotify.h"
#include "Animations/STUEquipFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Animations/AnimUtils.h"

constexpr static int32 WeaponNum = 2;

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

class ASTUBaseWeapon;
// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only %i weapon items"), WeaponNum);

    InitAnimations();
    CurrentWeaponIndex = 0;
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon *Weapon, USceneComponent *SceneComponent,
                                               const FName &SocketName)
{
    if (!Weapon || !SceneComponent)
        return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
        return;;
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponSecondSocket);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData &Data) {
        //
        return Data.WeaponClasses == CurrentWeapon->GetClass(); //
    });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocket);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::SpawnWeapons()
{
    if (!GetWorld())
        return;

    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClasses);
        if (!Weapon)
            continue;

        Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
        Weapon->SetOwner(GetOwner());
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponSecondSocket);
    }
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage *AnimMontage) const
{
    ACharacter *Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return;

    Player->PlayAnimMontage(AnimMontage);
}

void USTUWeaponComponent::InitAnimations()
{
    const auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
        checkNoEntry();
    }

    for (const auto OneWeaponData : WeaponData)
    {
        const auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if (!ReloadFinishedNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
            checkNoEntry();
        }
        ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent *MeshComp)
{
    ACharacter *Player = Cast<ACharacter>(GetOwner());
    if (!Player || Player->GetMesh() != MeshComp)
        return;

    EquipAnimInProgress = false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent *MeshComp)
{
    ACharacter *Player = Cast<ACharacter>(GetOwner());
    if (!Player || Player->GetMesh() != MeshComp)
        return;

    ReloadAnimInProgress = false;
}

bool USTUWeaponComponent::CanReload()
{
    return CurrentWeapon //
           && !EquipAnimInProgress//
           && !ReloadAnimInProgress//
           && CurrentWeapon->CanReload();
}

void USTUWeaponComponent::OnEmptyClip(ASTUBaseWeapon* AmmoEmptyWeapon)
{
    if(!AmmoEmptyWeapon) return;
    
    if(CurrentWeapon == AmmoEmptyWeapon)
    {
        ChangeClip();
    }
    else
    {
        for (const auto Weapon : Weapons)
        {
            if (Weapon == AmmoEmptyWeapon)
            {
                Weapon->ChangeClip();
            }
        }
    }
}

void USTUWeaponComponent::ChangeClip()
{
    if (!CanReload())
        return;

    ReloadAnimInProgress = true;
    CurrentWeapon->StopFire();
    PlayAnimMontage(CurrentReloadAnimMontage);
    CurrentWeapon->ChangeClip();
}

bool USTUWeaponComponent::CanFire()
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanEquip()
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::StartFire()
{
    if (!CanFire())
        return;
    CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;

    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::Reload()
{
    ChangeClip();
}

bool USTUWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData &UIData) const
{
    if (CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

bool USTUWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData &AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetCurrentAmmoData();
        return  true;
    }
    return false;
}

bool USTUWeaponComponent::TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount)
{
    for (const auto Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(ClipsAmount);
        }
    }
    return false;
}

bool USTUWeaponComponent::NeedAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType)
{
    for (const auto Weapon : Weapons)
    {
        if(Weapon && Weapon->IsA(WeaponType))
        {
            return !Weapon->IsAmmoFull();
        }
    }
    return false;
}

