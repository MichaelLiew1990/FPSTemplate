#pragma once

#include "GameFramework/GameState.h"
#include "BaseGameState.generated.h"

UCLASS()
class FPSTEMPLATE_API ABaseGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		TEnumAsByte<ETeamEnum> MatchWinner;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		ABasePlayerState * WinnerPlayerState;

	// Remaining time seconds for the match/round
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		int32 TimeRemaining;
	
	void DefaultTimer() override;
	
};
