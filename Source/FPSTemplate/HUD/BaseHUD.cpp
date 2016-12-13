#include "FPSTemplate.h"
#include "BaseHUD.h"

ABaseHUD::ABaseHUD()
{
	bShowOverlays = true;
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create MainWidget from MainWidgetClass
	MainWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainWidgetClass);
	if (MainWidget)
	{
		MainWidget->AddToViewport();
	}
}

void ABaseHUD::Destroyed()
{
	Super::Destroyed();

	if (MainWidget)
	{
		// Remove MainWidget when this HUD gets destroyed
		MainWidget->RemoveFromParent();
	}
}

void ABaseHUD::SetWidgetVisibility(bool bVisible)
{
	if (MainWidget)
	{
		MainWidget->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}