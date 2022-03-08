// Shoot Them Up Game


#include "UI/STUHealtBarWidget.h"

#include "Components/ProgressBar.h"

void USTUHealtBarWidget::SetHealthPercent(float Percent)
{
    if (!HealthProgressBar) return;

    const auto HealthBarVisiblity = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
                                        ? ESlateVisibility::Hidden
                                        : ESlateVisibility::Visible;

    HealthProgressBar->SetVisibility(HealthBarVisiblity);

    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}
