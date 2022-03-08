// Shoot Them Up Game


#include "UI/STUGameDataWidget.h"



int32 USTUGameDataWidget::GetCurrentRound() const
{
    const auto STUGameMode = GetSTUGameMode();
    return STUGameMode ? STUGameMode->GetCurrentRound() : 0;
}

int32 USTUGameDataWidget::GetTotalRoundNum() const
{
    const auto STUGameMode = GetSTUGameMode();
    return STUGameMode ? STUGameMode->GetGameData().RoundsNum : 0;
}

int32 USTUGameDataWidget::GetRoundSecondsRemaining() const
{
    const auto STUGameMode = GetSTUGameMode();
    return STUGameMode ? STUGameMode->GetRoundSecondsRemaining() : 0;
}

ASTUGameModeBase* USTUGameDataWidget::GetSTUGameMode() const
{
    return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const
{
    return GetOwningPlayer() ? GetOwningPlayer()->GetPlayerState<ASTUPlayerState>() : nullptr;
}
