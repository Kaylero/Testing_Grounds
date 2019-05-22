// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	auto AIController = OwnerComp.GetAIOwner();
	if (!ensure(AIController)) { return EBTNodeResult::Failed; }

	auto Pawn = AIController->GetPawn();
	if (!ensure(Pawn)) { return EBTNodeResult::Failed; }

	auto PatrolRouteComponent = Pawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRouteComponent)) { return EBTNodeResult::Failed; }

	auto RoutePoints = PatrolRouteComponent->GetRoutePoints();

	if (RoutePoints.Num() == 0) { return EBTNodeResult::Failed; }

	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, RoutePoints[Index]);

	Index++;
	Index = Index % RoutePoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}
