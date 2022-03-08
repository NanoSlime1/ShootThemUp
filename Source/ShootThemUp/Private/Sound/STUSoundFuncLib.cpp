// Shoot Them Up Game


#include "Sound/STUSoundFuncLib.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUSoundClassFuncLib, All, All);

void USTUSoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if(!SoundClass) return;

    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 100.0f);
    UE_LOG(LogSTUSoundClassFuncLib, Display, TEXT("Sound class volume was changed: %s = %f"), *SoundClass->GetName(), SoundClass->Properties.Volume);
    
}

void USTUSoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if(!SoundClass) return;

    const auto NextSound = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
    SetSoundClassVolume(SoundClass, NextSound);
}
