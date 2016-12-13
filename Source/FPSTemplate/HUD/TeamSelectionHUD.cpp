#include "FPSTemplate.h"
#include "TeamSelectionHUD.h"

ATeamSelectionHUD::ATeamSelectionHUD()
{
	static ConstructorHelpers::FObjectFinder<UObject> NewMainWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/WBP_TeamSelection.WBP_TeamSelection_C'"));
	MainWidgetClass = (UClass*)NewMainWidgetClass.Object;
}