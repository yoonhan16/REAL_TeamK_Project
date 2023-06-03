// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomPatrol_Basic.h"
#include "BP_Basic_Zombie.h"
#include "Ai_Controller_BasicZombie.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

//return EBTNodeResult::Type();

UBTTask_FindRandomPatrol_Basic::UBTTask_FindRandomPatrol_Basic()
{
	NodeName = TEXT("FindRandomPatrol_Basic");
}

EBTNodeResult::Type UBTTask_FindRandomPatrol_Basic::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UE_LOG(LogTemp, Warning, TEXT("Start patrol : Called"));

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Find Vaild Pawn : Called"));

		return EBTNodeResult::Failed;
	}

	ABP_Basic_Zombie* BasicZombie = Cast<ABP_Basic_Zombie>(OwnerComp.GetAIOwner()->GetPawn());
	BasicZombie->UpdateSpeed(150.0f);


	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Find NavMesh : Called"));

		return EBTNodeResult::Failed;
	}

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AAi_Controller_BasicZombie::Key_PatrolLocation_Home);
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 2000.0f, NextPatrol))
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Vaild Location : Called"));
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AAi_Controller_BasicZombie::Key_PatrolLocation_Target, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

