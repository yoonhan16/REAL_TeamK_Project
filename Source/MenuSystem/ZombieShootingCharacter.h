//// Copyright Epic Games, Inc. All Rights Reserved.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
//#include "InputActionValue.h"
//#include "Interact_Interface.h"
//#include "ZombieShootingCharacter.generated.h"
//
//
//UCLASS(config = Game)
//class AZombieShootingCharacter : public ACharacter, public IInteract_Interface
//{
//	GENERATED_BODY()
//
//		/** Camera boom positioning the camera behind the character */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
//		class USpringArmComponent* CameraBoom;
//
//	/** Follow camera */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
//		class UCameraComponent* FollowCamera;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = "true"))
//		class USpotLightComponent* FlashLight;
//
//	/** MappingContext */
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
//		class UInputMappingContext* DefaultMappingContext;
//
//	/** Jump Input Action */
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
//		class UInputAction* JumpAction;
//
//	/** Move Input Action */
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
//		class UInputAction* MoveAction;
//
//	/** Look Input Action */
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
//		class UInputAction* LookAction;
//
//	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
//	//class UInputAction* Interact;
//
//public:
//	AZombieShootingCharacter();
//
//
//protected:
//
//	/** Called for movement input */
//	void Move(const FInputActionValue& Value);
//
//	/** Called for looking input */
//	void Look(const FInputActionValue& Value);
//
//
//protected:
//	// APawn interface
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//
//	// To add mapping context
//	virtual void BeginPlay() override;
//
//public:
//	/** Returns CameraBoom subobject **/
//	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
//	/** Returns FollowCamera subobject **/
//	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
//
//	virtual void Tick(float DeltaSeconds) override;
//
//private:
//
//	void OnInteract();
//
//	UPROPERTY(EditAnywhere)
//		float InteractLineTraceLength = 200.f;
//
//	IInteract_Interface* Interface = nullptr;
//
//};