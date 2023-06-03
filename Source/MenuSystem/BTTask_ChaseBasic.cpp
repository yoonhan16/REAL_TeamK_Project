// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChaseBasic.h"
#include "BP_Basic_Zombie.h"
#include "MenuSystemCharacter.h"
#include "Ai_Controller_BasicZombie.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

//return EBTNodeResult::Type();

UBTTask_ChaseBasic::UBTTask_ChaseBasic()
{
	NodeName = TEXT("ChaseBasic");
}

EBTNodeResult::Type UBTTask_ChaseBasic::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UE_LOG(LogTemp, Warning, TEXT("Start Chase : Called"));

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ABP_Basic_Zombie* Basic_Zombie = Cast<ABP_Basic_Zombie>(OwnerComp.GetAIOwner()->GetPawn());
	Basic_Zombie->UpdateSpeed(700.0f);
	
	AMenuSystemCharacter* PlayerCharactor = Cast<AMenuSystemCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AAi_Controller_BasicZombie::Key_EnemyActor));
	if (nullptr == PlayerCharactor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find Player : Called"));
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	






	return EBTNodeResult::Succeeded;




}


