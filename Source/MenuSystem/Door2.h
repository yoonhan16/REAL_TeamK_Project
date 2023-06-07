// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Interact_Interface.h"
#include "Door2.generated.h"

UCLASS()
class MENUSYSTEM_API ADoor2 : public AActor, public IInteract_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor2();

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		class UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* LeftDoor;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* RightDoor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnInteract();

	class AJuno_CPPCharacter* Character;
	//UFUNCTION(BlueprintCallable)
		virtual void MyInteract_Implementation() override;

private:


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
