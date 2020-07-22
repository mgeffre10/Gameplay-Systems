// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TaskManagerSubsystem.h"
#include "TSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TASKSYSTEM_API UTSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:

	// Task System
	UPROPERTY()
	UTaskManagerSubsystem* TaskSystem;

	UFUNCTION(BlueprintCallable)
	UTaskManagerSubsystem* GetTaskSystem();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCurrentTaskWidget(FTaskStruct Task);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTaskListWidget();
};
