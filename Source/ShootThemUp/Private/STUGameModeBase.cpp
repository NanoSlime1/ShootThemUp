// Shoot Them Up Game
#include "STUGameModeBase.h"


#include "Player/STUBaseCharacter.h"
#include "STUPlayerController.h"
#include "UI/STUGameHUD.h"


ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}
