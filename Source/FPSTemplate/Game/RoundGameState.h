#pragma once

#include "Game/BaseGameState.h"
#include "RoundGameState.generated.h"

UENUM(BlueprintType)
namespace ERoundStateEnum
{
	enum Type
	{
		WarmUp,
		PreRound,
		InProgress,
		RoundEnd,
	};
}

UCLASS()
class FPSTEMPLATE_API ARoundGameState : public ABaseGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		TEnumAsByte<ERoundStateEnum::Type> RoundState;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		int32 TeamARoundsWon;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		int32 TeamBRoundsWon;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		int32 NumRoundsPerHalf;
	
	
};
