#pragma once

#include "Game/BaseGameMode.h"
#include "FreeForAll.generated.h"

UCLASS()
class FPSTEMPLATE_API AFreeForAll : public ABaseGameMode
{
	GENERATED_BODY()

public:
	AFreeForAll(const FObjectInitializer & ObjectInitializer);
	
	virtual void OnPlayerKilledEnemy(const FDamageEvent & DamageEvent, ABasePlayerController * PC, ABasePlayerController * OtherPC) override;
	
};
