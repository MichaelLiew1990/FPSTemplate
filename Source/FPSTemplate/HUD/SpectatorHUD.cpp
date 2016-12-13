#include "FPSTemplate.h"
#include "SpectatorHUD.h"

ASpectatorHUD::ASpectatorHUD()
{
	static ConstructorHelpers::FObjectFinder<UObject> NewMainWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/WBP_Spectator.WBP_Spectator_C'"));
	MainWidgetClass = (UClass*)NewMainWidgetClass.Object;
}