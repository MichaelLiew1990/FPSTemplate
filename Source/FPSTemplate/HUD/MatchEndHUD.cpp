#include "FPSTemplate.h"
#include "MatchEndHUD.h"


AMatchEndHUD::AMatchEndHUD()
{
	static ConstructorHelpers::FObjectFinder<UObject> NewMainWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/WBP_MatchEnd.WBP_MatchEnd_C'"));
	MainWidgetClass = (UClass*)NewMainWidgetClass.Object;
}