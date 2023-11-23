// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "ValShootMechanicCharacter.h"
#include "ValShootMechanicProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ValShootMechanicHUD.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	// Initialized bools
	bIsDamageDropoffApplied = false;
	bIsHeadShot = false;
	bIsBodyShot = false;
	bIsLegShot = false;
}


void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a raycast
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());

	// Get the screen dimensions, will be used to to set the raycast's Z axis
    int32 ScreenWidth, ScreenHeight;
    PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
    // Calculate the center of the screen
    FVector2D ScreenCenter(ScreenWidth / 2, ScreenHeight / 2);
    // Convert screen coordinates to world space
    FVector WorldLocation, WorldDirection;
    PlayerController->DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection);

	// Get the characters direction from the PlayerController's current camera 
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	// Set the start of the raycast, creating a vector using the character's location X/Y axis and the calculated screen center's location Z axis
	FVector Start = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, WorldLocation.Z);
	// Raycast range will be 50 meters(1 UU = 1 cm) so 5000 UU
	FVector End = Start + SpawnRotation.Vector() * 5000;
	FHitResult HitResult;

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		// Raycast query parameters to ignore character shooting the raycast
		FCollisionQueryParams RayQuery;
		RayQuery.AddIgnoredActor(GetOwner());

		// Bool is returned from raycast function 
		bool bIsActorHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, RayQuery, FCollisionResponseParams());
		DrawDebugLine(World, Start, End, FColor::Red, false, 2.f, 0.f, 0.f);

		// Get instance of HUD
		AValShootMechanicHUD* HUD = Cast<AValShootMechanicHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		
		AActor* HitActor = HitResult.GetActor();
		// Check if user shot the other character 
		USkeletalMeshComponent* CheckMesh = HitActor->GetComponentByClass<USkeletalMeshComponent>();
		if (HitActor && CheckMesh && HitActor != GetOwner())
		{
			// Get distance between characters 
			FVector ActorDifference = HitActor->GetActorLocation() - Character->GetActorLocation();

			// Get bone name from character's body
			FName BoneName = HitResult.BoneName;

			// Check to see if damage dropoff can be applied 
			if (ActorDifference.Length() > 3000.0f)
			{
				bIsDamageDropoffApplied = true;
			}
			else
			{
				bIsDamageDropoffApplied = false;
			}

			// Get location of shot, the 3rd party mesh has a different naming for each part of the body
			// Head shot
			if (BoneName == "Neck")
			{
				bIsHeadShot = true;
				bIsBodyShot = false;
				bIsLegShot = false;
			}
			// Body shot
			else if (BoneName == "Spine3" || BoneName == "L_Elbow" || BoneName == "R_Shoulder" || BoneName == "Pelvis")
			{
				bIsHeadShot = false;
				bIsBodyShot = true;
				bIsLegShot = false;
			}
			// Leg shot
			else if (BoneName == "L_Hip" || BoneName == "R_Hip")
			{
				bIsHeadShot = false;
				bIsBodyShot = false;
				bIsLegShot = true;
			}

			// Apply damage dropoff to differnt shots 
			if (bIsDamageDropoffApplied)
			{
				if (bIsHeadShot)
				{
					HUD->GetHUDWidget()->SetBodyLocationDamage(FText::FromString(TEXT("Head Shot")), HEAD_DAMAGE * DAMAGE_DROPOFF_MULTIPLER);
				}
				else if (bIsBodyShot)
				{
					HUD->GetHUDWidget()->SetBodyLocationDamage(FText::FromString(TEXT("Body Shot")), BODY_DAMAGE * DAMAGE_DROPOFF_MULTIPLER);
				}
				else if (bIsLegShot)
				{
					HUD->GetHUDWidget()->SetBodyLocationDamage(FText::FromString(TEXT("Leg Shot")), LEG_DAMAGE * DAMAGE_DROPOFF_MULTIPLER);

				}
			}
			else
			{
				if (bIsHeadShot)
				{
					HUD->GetHUDWidget()->SetBodyLocationDamage(FText::FromString(TEXT("Head Shot")), HEAD_DAMAGE);
				}
				else if (bIsBodyShot)
				{
					HUD->GetHUDWidget()->SetBodyLocationDamage(FText::FromString(TEXT("Body Shot")), BODY_DAMAGE);
				}
				else if (bIsLegShot)
				{
					HUD->GetHUDWidget()->SetBodyLocationDamage(FText::FromString(TEXT("Leg Shot")), LEG_DAMAGE);

				}
			}
			
		}
		else
		{
			HUD->GetHUDWidget()->SetBodyLocationDamage(FText::FromString(TEXT("Missed Shot")), 0);
		}

	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::AttachWeapon(AValShootMechanicCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr || Character->GetHasRifle())
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		}
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}