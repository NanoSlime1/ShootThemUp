#pragma once

class STUUtils
{
public:
    template<typename T>
    static T* GetSTUPlayerComponent(AActor* PlayerActor)
    {
        if(!PlayerActor) return nullptr;

        const auto Component = PlayerActor->FindComponentByClass<T>();
        if(!Component) return nullptr;

        return Component;
    }
};