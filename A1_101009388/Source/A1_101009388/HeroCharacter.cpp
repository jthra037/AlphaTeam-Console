// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "A1_101009388.h"
#include "HeroCharacter.h"
#include "A1PlayerController.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"


// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	lastTick = sideScroller;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->JumpZVelocity *= 1.7;
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (lastTick != sideScroller)
	//{
	//	SwitchCam();
	//	lastTick = sideScroller;
	//}

}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AHeroCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);
	//InputComponent->BindAction("Jump", IE_Pressed, this, &AHeroCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AHeroCharacter::Jump);

}

void AHeroCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();

		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHeroCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !sideScroller)
	{
		const FRotator Rotation = Controller->GetControlRotation();

		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AHeroCharacter::Jump()
{
	Super::Jump();
}


void AHeroCharacter::SwitchCam()
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (controller == nullptr)
		return;

	GLog->Log("We got to the for loop");

	
	
	for (TActorIterator<ACameraActor> It(GetWorld()); It; ++It)
	{
		ACameraActor* thisCamera = *It;
		GLog->Log(thisCamera->GetName());
		if (sideScroller && thisCamera->GetName().Compare("SceneCamera") == 0)
			controller->SetViewTargetWithBlend(thisCamera);
		
		if (!sideScroller && thisCamera->GetName().Compare("SceneCamera") != 0)
			controller->SetViewTargetWithBlend(thisCamera);
	}
}