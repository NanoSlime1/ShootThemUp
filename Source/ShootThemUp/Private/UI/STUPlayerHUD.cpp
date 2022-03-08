// Shoot Them Up Game

#include "STUPlayerHUD.h"
#include "STUWeaponComponent.h"
#include "STUHealthComponent.h"
#include "STUUtils.h"
#include "Components/ProgressBar.h"

float USTUPlayerHUD::GetHealthPercent() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUD::GetCurrentWeaponUIData(FWeaponUIData &UIData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTUPlayerHUD::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USTUPlayerHUD::IsPlayerAlive() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUD::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

void USTUPlayerHUD::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUD::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

int32 USTUPlayerHUD::GetKillsNum() const
{
    const auto Controller = GetOwningPlayer();
    if(!Controller) return 0;

    const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString USTUPlayerHUD::FormatBullets(int32 BulletsNum) const
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';

    auto BulletStr = FString::FromInt(BulletsNum);
    const auto SymbolNumToAdd = MaxLen - BulletStr.Len();

    if(SymbolNumToAdd > 0)
    {
        BulletStr = FString::ChrN(SymbolNumToAdd, PrefixSymbol).Append(BulletStr);
    }

    return BulletStr;
    
}

void USTUPlayerHUD::OnHealthChanged(float Health, float HeathDelta)
{
    if(HeathDelta < 0.0f)
    {
        OnTakeDamage();

        if(!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }

    UpdateHealthBar();
}

void USTUPlayerHUD::OnNewPawn(APawn* Pawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);
    if(HealthComponent && !HealthComponent->OnChangeHealth.IsBoundToObject(this))
    {
        HealthComponent->OnChangeHealth.AddUObject(this, &USTUPlayerHUD::OnHealthChanged);
    }

    UpdateHealthBar();
}

void USTUPlayerHUD::UpdateHealthBar()
{
    if(HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
}
