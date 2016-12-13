#include "FPSTemplate.h"
#include "BombAreaVolume.h"

ABombAreaVolume::ABombAreaVolume()
{
	GetBrushComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
}