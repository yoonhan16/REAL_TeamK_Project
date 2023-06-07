//// Copyright Epic Games, Inc. All Rights Reserved.
//
//#include "ZombieShootingCharacter.h"
//#include "Camera/CameraComponent.h"
//#include "Components/CapsuleComponent.h"
//#include "Components/InputComponent.h"
//#include "Components/BoxComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "GameFramework/Controller.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"
//#include "Door.h"
//#include "Door2.h"
//#include "Elevator.h"
//#include "DrawDebugHelpers.h"                // ����� �� ���� �����ֱ� ��
//#include "Components/SpotLightComponent.h"
//
//
////////////////////////////////////////////////////////////////////////////
//// AJuno_CPPCharacter
//
//AZombieShootingCharacter::AZombieShootingCharacter()
//{
//	// Set size for collision capsule
//	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
//
//	// Don't rotate when the controller rotates. Let that just affect the camera.
//	bUseControllerRotationPitch = false;
//	bUseControllerRotationYaw = false;
//	bUseControllerRotationRoll = false;
//
//	// Configure character movement
//	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
//	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
//
//	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
//	// instead of recompiling to adjust them
//	GetCharacterMovement()->JumpZVelocity = 700.f;
//	GetCharacterMovement()->AirControl = 0.35f;
//	GetCharacterMovement()->MaxWalkSpeed = 800.f;
//	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
//	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
//
//	// Create a camera boom (pulls in towards the player if there is a collision)
//	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
//	CameraBoom->SetupAttachment(RootComponent);
//	CameraBoom->TargetArmLength = 0.0f; // The camera follows at this distance behind the character	
//	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
//	CameraBoom->SetRelativeLocation(FVector(10.0f, 0.0f, 70.0f));
//
//	// Create a follow camera
//	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
//	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
//	FollowCamera->SetFieldOfView(110.0f);
//	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
//	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
//	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
//
//	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
//	FlashLight->SetupAttachment(CameraBoom);
//}
//
//void AZombieShootingCharacter::BeginPlay()
//{
//	// Call the base class  
//	Super::BeginPlay();
//
//	//InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AJuno_CPPCharacter::OnBoxBeginOverlap);
//
//	//Add Input Mapping Context
//	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
//	{
//		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
//		{
//			Subsystem->AddMappingContext(DefaultMappingContext, 0);
//		}
//	}
//}
//
//void AZombieShootingCharacter::Tick(float DeltaSeconds)
//{
//	Super::Tick(DeltaSeconds);
//}
//
//void AZombieShootingCharacter::OnInteract()
//{
//
//	if (FollowCamera == nullptr) return;
//
//	FHitResult HitResult;
//	FVector Start = FollowCamera->GetComponentLocation();
//	FVector End = Start + FollowCamera->GetForwardVector() * InteractLineTraceLength;
//	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
//	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f);
//	DrawDebugPoint(GetWorld(), End, 20.f, FColor::Red, false, 2.f);
//	DrawDebugPoint(GetWorld(), Start, 20.f, FColor::Blue, false, 2.f);
//
//	Interface = Cast<IInteract_Interface>(HitResult.GetActor());
//
//	if (Interface)
//	{
//		Interface->Interact();
//	}
//
//}
//
//void AZombieShootingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
//{
//	// Set up action bindings
//	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
//
//		//Jumping
//		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
//		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
//
//		//Moving
//		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJuno_CPPCharacter::Move);
//
//		//Looking
//		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AJuno_CPPCharacter::Look);
//
//	}
//
//	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AJuno_CPPCharacter::OnInteract);
//}
//
//void AZombieShootingCharacter::Move(const FInputActionValue& Value)
//{
//	// input is a Vector2D
//	FVector2D MovementVector = Value.Get<FVector2D>();
//
//	if (Controller != nullptr)
//	{
//		// find out which way is forward
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//		// get forward vector
//		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//
//		// get right vector 
//		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//
//		// add movement 
//		AddMovementInput(ForwardDirection, MovementVector.Y);
//		AddMovementInput(RightDirection, MovementVector.X);
//	}
//}
//
//void AZombieShootingCharacter::Look(const FInputActionValue& Value)
//{
//	// input is a Vector2D
//	FVector2D LookAxisVector = Value.Get<FVector2D>();
//
//	if (Controller != nullptr)
//	{
//		// add yaw and pitch input to controller
//		AddControllerYawInput(LookAxisVector.X);
//		AddControllerPitchInput(LookAxisVector.Y);
//	}
//}
