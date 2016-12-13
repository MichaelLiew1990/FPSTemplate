#include "FPSTemplate.h"
#include "ScoreboardSlotWidget.h"

ABasePlayerState * UScoreboardSlotWidget::GetPlayerState() const
{
	return PlayerState;
}

void UScoreboardSlotWidget::SetPlayerState(ABasePlayerState * NewPlayerState)
{
	PlayerState = NewPlayerState;
}