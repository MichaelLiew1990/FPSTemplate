#include "FPSTemplate.h"
#include "DeathHUD.h"

ADeathHUD::ADeathHUD()
{
	static ConstructorHelpers::FObjectFinder<UObject> NewMainWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/WBP_Death.WBP_Death_C'"));
	MainWidgetClass = (UClass*)NewMainWidgetClass.Object;
}