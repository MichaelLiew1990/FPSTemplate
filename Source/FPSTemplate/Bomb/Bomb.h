#pragma once

#include "Soldier/Soldier.h"
#include "Items/Item.h"
#include "Bomb.generated.h"

// Class for a bomb in BombDefuse game mode
UCLASS()
class FPSTEMPLATE_API ABomb : public AItem
{
	GENERATED_BODY()

	FTimerHandle TimerHandle_Explode;

public:
	// Animation for arming the bomb
	UPROPERTY(EditDefaultsOnly, Category = Animations)
		FItemAnimation ArmAnimation;

	// Whether bomb is planted and can be defused
	UPROPERTY(ReplicatedUsing = OnRep_bArmed, BlueprintReadOnly, Category = Bomb)
		bool bArmed;

	UFUNCTION()
		void OnRep_bArmed();

	ABomb(const FObjectInitializer & ObjectInitializer);

	virtual bool CanBePickedUp() const override;

	// Explode this bomb, i.e. apply damage and end the round
	void Explode();

	// Returns remaining time to explosion
	UFUNCTION(BlueprintPure, Category = Bomb)
		float GetRemainingTime() const;

	virtual void StartFiring() override;

	virtual void OnFired() override;

	virtual void OnFire() override;

	// Interaction interface used for defusing
	virtual bool CanSoldierInteract(ASoldier * Soldier) const override;
	
	virtual float GetInteractionLength() const override;

	virtual FVector GetInteractionLocation() const override;

	virtual void OnInteract(ASoldier * Soldier) override;
	
};
