#include "FPSTemplate.h"
#include "Bomb.h"
#include "UnrealNetwork.h"
#include "Game/BombDefuse.h"
#include "Bomb/BombAreaVolume.h"

#define TimeToExplode 30.f

ABomb::ABomb(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemSlot = EItemSlotEnum::Secondary;
}

void ABomb::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABomb, bArmed);
}

bool ABomb::CanBePickedUp() const
{
	// Bomb can only be picked up when not planted
	return Super::CanBePickedUp() && !bArmed;
}

void ABomb::Explode()
{
	ABombDefuse * GameMode = Cast<ABombDefuse>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		// Check if bomb exploded in bomb area
		bool bInBombArea = false;
		for (TActorIterator<ABombAreaVolume> VolumeItr(GetWorld()); VolumeItr; ++VolumeItr)
		{
			if (VolumeItr->IsOverlappingActor(this))
			{
				bInBombArea = true;
				break;
			}
		}

		// Terrorists only win when bomb exploded in the bomb area
		if (bInBombArea)
		{
			GameMode->EndRound(ETeamEnum::TeamB);
		}
		else
		{
			GameMode->EndRound(ETeamEnum::TeamA);
		}
	}

	Destroy();
}

float ABomb::GetRemainingTime() const
{
	return GetWorldTimerManager().GetTimerRemaining(TimerHandle_Explode);
}

void ABomb::StartFiring()
{
	if (PerformTask(EItemTaskEnum::Fire, ArmAnimation.Length))
	{
		OnFire();
	}
}

void ABomb::OnFired()
{
	bArmed = true;
	GetWorldTimerManager().SetTimer(TimerHandle_Explode, this, &ABomb::Explode, TimeToExplode);

	ASoldier * Soldier = GetOwningSoldier();
	if (Soldier)
	{
		// Bomb is armed, drop it
		Soldier->DropItem();
	}

	ABombDefuse * GameMode = Cast<ABombDefuse>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		// Notif game mode that bomb was armed
		GameMode->OnBombArmed();
	}
}

void ABomb::OnFire()
{
	PlayAnimation(ArmAnimation);
}

bool ABomb::CanSoldierInteract(ASoldier * Soldier) const
{
	// Soldiers can only interact if they are not in terrorist team and the bomb is actually planted
	return bArmed && Soldier->GetTeam() == ETeamEnum::TeamA;
}

float ABomb::GetInteractionLength() const
{
	return 4.f;
}

FVector ABomb::GetInteractionLocation() const
{
	return GetActorLocation();
}

void ABomb::OnInteract(ASoldier * Soldier)
{
	bArmed = false;

	ABombDefuse * GameMode = Cast<ABombDefuse>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		// Bomb defused, terrorists lose
		GameMode->EndRound(ETeamEnum::TeamA);
	}
}

void ABomb::OnRep_bArmed()
{
	if (bArmed)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_Explode, TimeToExplode, false);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Explode);
	}
}