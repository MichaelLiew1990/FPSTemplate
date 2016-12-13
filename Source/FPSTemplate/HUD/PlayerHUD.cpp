#include "FPSTemplate.h"
#include "PlayerHUD.h"
#include "Player/BasePlayerController.h"
#include "Player/BasePlayerState.h"
#include "Soldier/Soldier.h"


APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FObjectFinder<UObject> NewMainWidgetClass(TEXT("WidgetBlueprint'/Game/FPSTemplate/HUD/Widgets/WBP_Player.WBP_Player_C'"));
	MainWidgetClass = (UClass*)NewMainWidgetClass.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> NewHitMarkerTexture(TEXT("Texture2D'/Game/FPSTemplate/HUD/Textures/T_hitmarker.T_hitmarker'"));
	HitMarkerTexture = NewHitMarkerTexture.Object;
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();

	ABasePlayerController * PC = Cast<ABasePlayerController>(GetOwningPlayerController());
	ABasePlayerState * OwnPlayer = Cast<ABasePlayerState>(GetOwningPlayerController() ? GetOwningPlayerController()->PlayerState : NULL);

	if (!PC || !OwnPlayer) return;

	//Draw soldiers
	for (TActorIterator<ASoldier> It(GetWorld(), ASoldier::StaticClass()); It; ++It)
	{
		ASoldier * Soldier = *It;
		if (ShouldDrawSoldier(Soldier))
		{
			const FVector Position = Project(Soldier->GetActorLocation() + FVector(0.f, 0.f, 100.f));
			if (Position.Z > 0.f)
			{
				ABasePlayerState * OtherPlayer = Cast<ABasePlayerState>(Soldier->PlayerState);
				if (OtherPlayer)
				{
					float TextWidth;
					float TextHeight;
					GetTextSize(OtherPlayer->PlayerName, TextWidth, TextHeight);

					DrawText(OtherPlayer->PlayerName, FLinearColor(0.1, 0.1, 1.f, 1.f), Position.X - TextWidth * 0.5f, Position.Y - TextHeight - 40.f, NULL, 1.f);
					//DrawTexture(UGameplayFunctionLibrary::GetSoldierClassIcon(OtherPlayer->SoldierClass), Position.X - 16.f, Position.Y - 32.f, 32.f, 32.f, 0.f, 0.f, 1.f, 1.f, Color);
				}
			}
		}
	}

	//Hitmarker
	if (HitMarkerOpacity > 0.f)
	{
		HitMarkerOpacity -= 0.05f;

		if (HitMarkerOpacity < 0.f)
		{
			HitMarkerOpacity = 0.f;
		}

		DrawTexture(HitMarkerTexture, Canvas->SizeX * 0.5f - 32.f, Canvas->SizeY * 0.5f - 32.f, 64.f, 64.f, 0.f, 0.f, 1.f, 1.f, FLinearColor(1.f, 1.f, 1.f, HitMarkerOpacity));
	}
}

void APlayerHUD::DrawActorOverlays(FVector Viewpoint, FRotator ViewRotation)
{
	Super::DrawActorOverlays(Viewpoint, ViewRotation);

	ASoldier * Soldier = Cast<ASoldier>(GetOwningPawn());
	if (Soldier)
	{
		Soldier->PostRenderFor(GetOwningPlayerController(), Canvas, Viewpoint, ViewRotation.Vector());
	}
}

bool APlayerHUD::ShouldDrawSoldier(ASoldier * Soldier) const
{
	APlayerController * PC = GetOwningPlayerController();
	ABasePlayerState * PS = PC ? Cast<ABasePlayerState>(PC->PlayerState) : NULL;
	if (PS && Soldier && !Soldier->IsDead() && Soldier->Controller != PC && !Soldier->IsEnemyFor(PS))
	{
		return Soldier->GetDistanceTo(PC->GetPawn()) < 1000.f || PC->LineOfSightTo(Soldier);
	}

	return false;
}

void APlayerHUD::NotifyHitEnemy(float Damage)
{
	HitMarkerOpacity = FMath::Clamp(HitMarkerOpacity + Damage * 0.01f, 0.5f, 1.f);
}