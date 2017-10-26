// Fill out your copyright notice in the Description page of Project Settings.

#include "A1_101009388.h"
#include "A1_101009388GameModeBase.h"

#include "A1PlayerController.h"
#include "UObject/ConstructorHelpers.h"

AA1_101009388GameModeBase::AA1_101009388GameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = AA1PlayerController::StaticClass();

	// Get the player pawn class
	// created and configured from editor
	static ConstructorHelpers::FObjectFinder<UClass>
		PlayerPawnBPClass(TEXT("Class'/Game/Character/HeroCharacter_BP.HeroCharacter_BP_C'"));
	if (PlayerPawnBPClass.Object != nullptr)
	{
		GLog->Log("Set DefaultPawn to HeroCharacter_BP");
		DefaultPawnClass = PlayerPawnBPClass.Object;
	}
	else
	{
		GLog->Log("Cannot find HeroCharacter_BP");
	}
}


