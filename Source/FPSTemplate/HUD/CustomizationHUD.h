#pragma once

#include "Game/LoadoutBuilderComponent.h"
#include "HUD/BaseHUD.h"
#include "CustomizationHUD.generated.h"

UCLASS()
class FPSTEMPLATE_API ACustomizationHUD : public ABaseHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = HUD)
		ULoadoutBuilderComponent * LoadoutBuilderComponent;

	ACustomizationHUD(const FObjectInitializer & ObjectInitializer);
	
};
