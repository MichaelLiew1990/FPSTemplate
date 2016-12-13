#pragma once

#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

UCLASS()
class FPSTEMPLATE_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

protected:
	// Widget class used for the base widget of this HUD
	UPROPERTY()
		TSubclassOf<UUserWidget> MainWidgetClass;

	// Instance of MainWidgetClass
	UPROPERTY()
		UUserWidget * MainWidget;

public:
	UUserWidget * GetMainWidget() const { return MainWidget; };

	ABaseHUD();

	void BeginPlay() override;

	void Destroyed() override;

	// Set visibility of child widgets, used for example to hide HUD in menu
	void SetWidgetVisibility(bool bVisible);
	
};