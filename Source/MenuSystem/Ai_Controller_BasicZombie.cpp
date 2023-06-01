// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai_Controller_BasicZombie.h"
#include "BP_Basic_Zombie.h"
#include "MenuSystemCharacter.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "EngineGlobals.h"



const FName AAi_Controller_BasicZombie::Key_HasLineOfSight(TEXT("HasLineOfSight"));
const FName AAi_Controller_BasicZombie::Key_EnemyActor(TEXT("EnemyActor"));
const FName AAi_Controller_BasicZombie::Key_PatrolLocation_Home(TEXT("PatrolLocation_Home"));
const FName AAi_Controller_BasicZombie::Key_PatrolLocation_Target(TEXT("PatrolLocation_Target"));


void AAi_Controller_BasicZombie::BeginPlay()
{
	Super::BeginPlay();
	ABP_Basic_Zombie* Enemy = Cast<ABP_Basic_Zombie>(GetPawn());
	if (Enemy)
	{
		BasicZombie = Enemy;
	}
}

AAi_Controller_BasicZombie::AAi_Controller_BasicZombie(const FObjectInitializer& ObjectInitializer)
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	Sight->SightRadius = 3000.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
	Sight->PeripheralVisionAngleDegrees = 80.0f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*Sight);
	AIPerceptionComponent->SetDominantSense(Sight->GetSenseImplementation());

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/TEAM_K/Left4Dead/KIM_YoonHan/BlackBoard/BB_BasicZombie.BB_BasicZombie"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("/Game/TEAM_K/Left4Dead/KIM_YoonHan/Behaviour_Tree/BT_BasicZombie.BT_BasicZombie"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

}


void AAi_Controller_BasicZombie::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	AMenuSystemCharacter* PlayerCharacter = Cast<AMenuSystemCharacter>(Actor);
	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter Not Found : Called"));


		return;
	}
	else
	{
		SetFocus(Stimulus.WasSuccessfullySensed() ? PlayerCharacter : nullptr);
		if (Stimulus.WasSuccessfullySensed() != NULL)
		{
			BlackboardComp->SetValueAsBool(Key_HasLineOfSight, true);

			if (PlayerCharacter->ActorHasTag("Player"))
			{
				BlackboardComp->SetValueAsObject(Key_EnemyActor, PlayerCharacter);
			}
		}
		else
		{
			BlackboardComp->SetValueAsBool(Key_HasLineOfSight, false);
			BlackboardComp->SetValueAsObject(Key_EnemyActor, nullptr);
		}
	}


}


void AAi_Controller_BasicZombie::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(Key_PatrolLocation_Home, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("AIController couldn't run behavior tree!"));
		}
	}

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAi_Controller_BasicZombie::OnPerception);


}



















//void AAi_Controller_BasicZombie::RunAI()
//{
//	if (UseBlackboard(BBAsset, BlackboardComp))
//	{
//
//		Blackboard
//
//
//		RunBehaviorTree(BTAsset);
//	}
//}

//void AAi_Controller_BasicZombie::StopAI()
//{
//	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
//	if (nullptr == BehaviorTreeComponent) return;
//
//	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
//}



