#pragma once

#include "Game/BaseGameMode.h"
#include "TeamDeathmatch.generated.h"

UCLASS()
class FPSTEMPLATE_API ATeamDeathmatch : public ABaseGameMode
{
	GENERATED_BODY()
	
public:
	ATeamDeathmatch(const FObjectInitializer & ObjectInitializer);

protected:
	virtual void InitGameState() override;

	virtual void OnPlayerDied(ABasePlayerController * PC) override;
	
	
};
