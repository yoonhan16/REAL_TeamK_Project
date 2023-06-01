// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindRandomPatrol_Basic.generated.h"

/**
 * 
 */
UCLASS()
class MENUSYSTEM_API UBTTask_FindRandomPatrol_Basic : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTask_FindRandomPatrol_Basic();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;




};
