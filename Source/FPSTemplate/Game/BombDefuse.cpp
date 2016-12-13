#include "FPSTemplate.h"
#include "BombDefuse.h"
#include "Game/BombDefuseGameState.h"
#include "Soldier/Soldier.h"

ABombDefuse::ABombDefuse(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ABombDefuseGameState::StaticClass();

	/*static ConstructorHelpers::FObjectFinder<UClass> NewBombClass(TEXT("Blueprint'/Game/FPSTemplate/Items/Bomb/BP_Bomb.BP_Bomb_C'"));
	BombClass = NewBombClass.Object;*/

	static ConstructorHelpers::FObjectFinder<UObject> NewScoreWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/GameState/WBP_BombDefuseScore.WBP_BombDefuseScore_C'"));
	ScoreWidgetClass = (UClass*)NewScoreWidgetClass.Object;
}

void ABombDefuse::OnRoundTimeExpired()
{
	// Terrorists lose when time expires
	EndRound(ETeamEnum::TeamA);
}

void ABombDefuse::NextRound()
{
	Super::NextRound();

	TArray<ASoldier *> SoldierArray;
	for (TActorIterator<ASoldier> SoldierItr(GetWorld()); SoldierItr; ++SoldierItr)
	{
		if (SoldierItr->GetTeam() == ETeamEnum::TeamB)
		{
			SoldierArray.Add(*SoldierItr);
		}
	}

	// Give a random member of terrorist team the bomb
	if (SoldierArray.Num() > 0)
	{
		ABombDefuseGameState * BombGameState = Cast<ABombDefuseGameState>(GameState);
		if (BombGameState)
		{
			BombGameState->Bomb = Cast<ABomb>(SoldierArray[FMath::RandRange(0, SoldierArray.Num() - 1)]->SpawnItem(BombClass));
		}
	}
}

void ABombDefuse::OnBombArmed()
{
	ABombDefuseGameState * BombGameState = Cast<ABombDefuseGameState>(GameState);
	if (BombGameState)
	{
		// Disable round timer when bomb was planted
		BombGameState->TimeRemaining = 0;
	}
}