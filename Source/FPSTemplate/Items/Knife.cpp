#include "FPSTemplate.h"
#include "Knife.h"
#include "Soldier/Soldier.h"

bool AKnife::CanBeDropped() const
{
	// A knife may never be dropped to acoid that players always have at least one item
	return false;
}

void AKnife::StartFiring()
{
	Fire();
}

void AKnife::Fire()
{
	if (PerformTask(EItemTaskEnum::Fire, StabAnimation.Length))
	{

		OnFire();
	}
}

void AKnife::OnFire()
{
	PlayAnimation(StabAnimation, 0.1f);

	ASoldier * Soldier = GetOwningSoldier();
	if (Soldier)
	{
		FHitResult Hit;
		// Execute stab logic on soldier
		if (Soldier->Stab(Hit, StabDamage, StabDistance))
		{
			SpawnImpactEffect(Hit);
		}
	}
}

void AKnife::SpawnImpactEffect(const FHitResult & HitResult)
{
	FImpactEffectStruct & ImpactEffect = MetalEffect;
	switch (UGameplayStatics::GetSurfaceType(HitResult))
	{
	case (SurfaceType1) :
		break;
	case (SurfaceType2) :
		ImpactEffect = StoneEffect;
		break;
	case (SurfaceType3) :
		ImpactEffect = WoodEffect;
		break;
	case (SurfaceType7) :
		ImpactEffect = FleshEffect;
		break;
	}

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect.ParticleEmitter, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
	UGameplayStatics::PlaySoundAtLocation(this, ImpactEffect.SoundCue, HitResult.ImpactPoint);
	UDecalComponent * Decal = UGameplayStatics::SpawnDecalAttached(ImpactEffect.DecalMaterial, FVector(ImpactEffect.DecalSize, ImpactEffect.DecalSize, 2.f), HitResult.Component.Get(), HitResult.BoneName, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), EAttachLocation::KeepWorldPosition, 20.f);
}