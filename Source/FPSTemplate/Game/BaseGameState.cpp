#include "FPSTemplate.h"
#include "BaseGameState.h"
#include "UnrealNetwork.h"
#include "Game/BaseGameMode.h"

void ABaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseGameState, MatchWinner);
	DOREPLIFETIME(ABaseGameState, WinnerPlayerState);
	DOREPLIFETIME(ABaseGameState, TimeRemaining);
}

void ABaseGameState::DefaultTimer()
{
	Super::DefaultTimer();

	if (IsMatchInProgress() && TimeRemaining > 0)
	{
		TimeRemaining--;

		if (TimeRemaining == 0)
		{
			ABaseGameMode * BaseGameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
			if (BaseGameMode)
			{
				// Notify game mode that match timed out
				BaseGameMode->OnTimeExpired();
			}
		}
	}
}