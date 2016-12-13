#pragma once

#include "Damage/BaseDamageType.h"
#include "Player/BasePlayerState.h"
#include "Blueprint/UserWidget.h"
#include "GameOverlayWidget.generated.h"

// Widget class for the main game overlay HUD. This class serves as an interface between C++ and UMG
UCLASS()
class FPSTEMPLATE_API UGameOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		UWidget * GetChatTextBox() const;

	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void OpenScoreboard();

	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void CloseScoreboard();

	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void ToggleLargeMiniMap();

	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void OnBeginChatMessage();

	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void ReceiveChatMessage(const FString & Message, ABasePlayerState * FromPlayer);

	// Kill feed notification
	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void OnPlayerDied(const UBaseDamageType * DamageType, ABasePlayerState * Player, ABasePlayerState * KillerPlayer);

	// Score notifications
	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void OnKilledEnemy(const UBaseDamageType * DamageType, ABasePlayerState * OtherPlayer, int32 Score);

	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void OnKilledTeammate(const UBaseDamageType * DamageType, ABasePlayerState * OtherPlayer, int32 Score);

	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void OnScored(const FText & ScoreMessage, int32 Score);

	// Damage
	UFUNCTION(BlueprintImplementableEvent, Category = Player)
		void OnTookDamage(float DamageAmount, AActor * Causer);
	
};
