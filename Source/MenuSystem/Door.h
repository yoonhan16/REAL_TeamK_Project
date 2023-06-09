// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Interact_Interface.h"
#include "Door.generated.h"

UCLASS()
class MENUSYSTEM_API ADoor : public AActor, public IInteract_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		class UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* Door;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UBoxComponent* BoxCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnInteract();

	class AJuno_CPPCharacter* Character;

	virtual void Interact() override;

protected:

	FTimeline Timeline;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UCurveFloat* CurveFloat;

	bool bIsDoorClosed = true;

	UPROPERTY(EditAnywhere)
		float DoorRotateAngle = 90.f;

	UFUNCTION()
		void OpenDoor(float Value);

	bool bDoorOnSameSide;
	void SetDoorOnSameSide();
};
