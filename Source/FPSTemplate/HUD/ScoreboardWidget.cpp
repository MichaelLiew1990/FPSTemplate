#include "FPSTemplate.h"
#include "ScoreboardWidget.h"
#include "Game/BaseGameMode.h"
#include "StaticFunctionLibrary.h"

UScoreboardWidget::UScoreboardWidget(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UObject> NewScoreboardSlotWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/WBP_ScoreboardSlot.WBP_ScoreboardSlot_C'"));
	ScoreboardSlotWidgetClass = (UClass*)NewScoreboardSlotWidgetClass.Object;
}

void UScoreboardWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ABasePlayerState * OwnerPS = Cast<ABasePlayerState>(GetOwningPlayer() ? GetOwningPlayer()->PlayerState : NULL);
	ABaseGameMode * GameModeCDO = UStaticFunctionLibrary::GetGameModeCDO(this);
	if (!OwnerPS || !GameModeCDO || !GetWorld()->GameState) return;

	// Iterate though all players and sort them after their score
	TArray<ABasePlayerState *> FriendlyPlayerStates;
	TArray<ABasePlayerState *> EnemyPlayerStates;
	for (APlayerState * It : GetWorld()->GameState->PlayerArray)
	{
		ABasePlayerState * PS = Cast<ABasePlayerState>(It);
		if (PS)
		{
			TArray<ABasePlayerState *> & PlayerStates = (GameModeCDO->TeamMode != ETeamModeEnum::MultipleTeams || OwnerPS == PS || !OwnerPS->IsEnemyFor(PS)) ? FriendlyPlayerStates : EnemyPlayerStates;
			uint32 Index = 0;
			for (ABasePlayerState * OtherPS : PlayerStates)
			{
				if (OtherPS && PS->Score > OtherPS->Score)
				{
					break;
				}

				Index++;
			}

			PlayerStates.Insert(PS, Index);
		}
	}

	// Update widgets if the order changed
	if (FriendlyPlayerStates != GetScoreboardFriendlyPlayerStates())
	{
		UpdateFriendlyPlayerStates(FriendlyPlayerStates);
	}

	if (EnemyPlayerStates != GetScoreboardEnemyPlayerStates())
	{
		UpdateEnemyPlayerStates(EnemyPlayerStates);
	}
}

void UScoreboardWidget::UpdateFriendlyPlayerStates(const TArray<ABasePlayerState *> & NewPlayerStates)
{
	UpdatePlayerStates(NewPlayerStates, GetFriendlyPlayersBox());
}

void UScoreboardWidget::UpdateEnemyPlayerStates(const TArray<ABasePlayerState *> & NewPlayerStates)
{
	UpdatePlayerStates(NewPlayerStates, GetEnemyPlayersBox());
}

void UScoreboardWidget::UpdatePlayerStates(const TArray<ABasePlayerState *> & NewPlayerStates, UVerticalBox * Container)
{
	if (!Container) return;

	Container->ClearChildren();

	for (ABasePlayerState * PS : NewPlayerStates)
	{
		UScoreboardSlotWidget * NewSlotWidget = CreateWidget<UScoreboardSlotWidget>(GetOwningPlayer(), ScoreboardSlotWidgetClass);
		if (NewSlotWidget)
		{
			NewSlotWidget->SetPlayerState(PS);
			Container->AddChild(NewSlotWidget);
		}
	}
}

TArray<ABasePlayerState *> UScoreboardWidget::GetScoreboardFriendlyPlayerStates() const
{
	return GetScoreboardPlayerStates(GetFriendlyPlayersBox());
}

TArray<ABasePlayerState *> UScoreboardWidget::GetScoreboardEnemyPlayerStates() const
{
	return GetScoreboardPlayerStates(GetEnemyPlayersBox());
}

TArray<ABasePlayerState *> UScoreboardWidget::GetScoreboardPlayerStates(UVerticalBox * Container) const
{
	TArray<ABasePlayerState *> PlayerStates;

	if (Container)
	{
		for (int32 i = 0; i < Container->GetChildrenCount(); i++)
		{
			UScoreboardSlotWidget * Widget = Cast<UScoreboardSlotWidget>(Container->GetChildAt(i));
			if (Widget)
			{
				PlayerStates.Add(Widget->GetPlayerState());
			}
		}
	}

	return PlayerStates;
}