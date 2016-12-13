#pragma once

#include "HUD/ScoreboardSlotWidget.h"
#include "Player/BasePlayerState.h"
#include "Blueprint/UserWidget.h"
#include "ScoreboardWidget.generated.h"

// Parent class for scoreboard widget
UCLASS()
class FPSTEMPLATE_API UScoreboardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
		TSubclassOf<UScoreboardSlotWidget> ScoreboardSlotWidgetClass;

	UScoreboardWidget(const FObjectInitializer & ObjectInitializer);

	void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;

	void UpdateFriendlyPlayerStates(const TArray<ABasePlayerState *> & NewPlayerStates);

	void UpdateEnemyPlayerStates(const TArray<ABasePlayerState *> & NewPlayerStates);

	void UpdatePlayerStates(const TArray<ABasePlayerState *> & NewPlayerStates, UVerticalBox * Container);

	TArray<ABasePlayerState *> GetScoreboardFriendlyPlayerStates() const;

	TArray<ABasePlayerState *> GetScoreboardEnemyPlayerStates() const;

	TArray<ABasePlayerState *> GetScoreboardPlayerStates(UVerticalBox * Container) const;

	UFUNCTION(BlueprintImplementableEvent, Category = Scoreboard)
		UVerticalBox * GetFriendlyPlayersBox() const;

	UFUNCTION(BlueprintImplementableEvent, Category = Scoreboard)
		UVerticalBox * GetEnemyPlayersBox() const;
	
	
};
