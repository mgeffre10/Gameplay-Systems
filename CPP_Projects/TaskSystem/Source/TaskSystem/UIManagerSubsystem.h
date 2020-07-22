// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TASKSYSTEM_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCurrentTaskWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTaskListWidget();
};
