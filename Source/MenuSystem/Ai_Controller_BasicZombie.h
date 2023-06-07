// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BP_Basic_Zombie.h"
#include "GenericTeamAgentInterface.h"
#include "Perception/AIPerceptionTypes.h"
#include "perception/AIPerceptionComponent.h"
#include "Ai_Controller_BasicZombie.generated.h"


/**
 * 
 */
UCLASS()
class MENUSYSTEM_API AAi_Controller_BasicZombie : public AAIController
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UBlackboardComponent* BlackboardComp = Blackboard;

	virtual void BeginPlay();

	FGenericTeamId TeamID;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:

	AAi_Controller_BasicZombie(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite)
	ABP_Basic_Zombie* BasicZombie;
	

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	static const FName Key_HasLineOfSight;
	static const FName Key_EnemyActor;
	static const FName Key_PatrolLocation_Home;
	static const FName Key_PatrolLocation_Target;

	class UAISenseConfig_Sight* Sight;
	class UAISenseConfig_Damage* Damage;
	class UAISenseConfig_Hearing* Hearing;

	virtual void OnPossess(APawn* InPawn) override;


private:

	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;


};
