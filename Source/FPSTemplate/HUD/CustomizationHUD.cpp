#include "FPSTemplate.h"
#include "CustomizationHUD.h"

ACustomizationHUD::ACustomizationHUD(const FObjectInitializer & ObjectInitializer)
{
	LoadoutBuilderComponent = ObjectInitializer.CreateDefaultSubobject<ULoadoutBuilderComponent>(this, TEXT("LoadoutBuilderComponent"));

	static ConstructorHelpers::FObjectFinder<UObject> NewMainWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/WBP_Customization.WBP_Customization_C'"));
	MainWidgetClass = (UClass*)NewMainWidgetClass.Object;
}