#include "FPSTemplate.h"
#include "SpawnHUD.h"

ASpawnHUD::ASpawnHUD()
{
	static ConstructorHelpers::FObjectFinder<UObject> NewMainWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/WBP_Spawn.WBP_Spawn_C'"));
	MainWidgetClass = (UClass*)NewMainWidgetClass.Object;
}