#include "FPSTemplate.h"
#include "MenuHUD.h"

AMenuHUD::AMenuHUD()
{
	static ConstructorHelpers::FObjectFinder<UObject> NewMainWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/WBP_Menu.WBP_Menu_C'"));
	MainWidgetClass = (UClass*)NewMainWidgetClass.Object;
}