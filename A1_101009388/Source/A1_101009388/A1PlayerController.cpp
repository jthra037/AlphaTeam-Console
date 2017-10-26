// Fill out your copyright notice in the Description page of Project Settings.

#include "A1_101009388.h"
#include "A1PlayerController.h"

#include "EngineUtils.h"
#include "Camera/CameraActor.h"

void AA1PlayerController::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ACameraActor> It(GetWorld()); It; ++It)
	{
		ACameraActor* MainCamera = *It;
		if (MainCamera->GetName().Compare("SceneCameraActor") == 0)
			this->SetViewTargetWithBlend(MainCamera);
	}
}


