#pragma once

#include "Player/BasePlayerState.h"
#include "Blueprint/UserWidget.h"
#include "ScoreboardSlotWidget.generated.h"

UCLASS()
class FPSTEMPLATE_API UScoreboardSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		ABasePlayerState * PlayerState;
	
public:
	UFUNCTION(Blueprintpure, Category = ScoreboardSlotWidget)
		ABasePlayerState * GetPlayerState() const;

	void SetPlayerState(ABasePlayerState * NewPlayerState);
	
};
