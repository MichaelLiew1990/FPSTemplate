#pragma once

#include "HUD/BaseHUD.h"
#include "PlayerHUD.generated.h"

UCLASS()
class FPSTEMPLATE_API APlayerHUD : public ABaseHUD
{
	GENERATED_BODY()

	// Value used for opacity of hit marker, will be more opaque with more damage instigated
	UPROPERTY()
		float HitMarkerOpacity;

	// Textures
	UPROPERTY()
		UTexture2D * HitMarkerTexture;

public:
	APlayerHUD();

	// Draw items on screen, e.g. other players
	void DrawHUD() override;

	// Draw HUD on soldier (e.g. crosshair)
	void DrawActorOverlays(FVector Viewpoint, FRotator ViewRotation) override;

private:
	// Returns whether a soldier should be shown on HUD or not
	bool ShouldDrawSoldier(ASoldier * Soldier) const;

public:
	// Event called when player damaged an enemy
	void NotifyHitEnemy(float Damage);
	
};
