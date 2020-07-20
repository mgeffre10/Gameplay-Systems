// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "TaskManagerSubsystem.generated.h"

UENUM()
enum ETaskStatus {
	ETS_NotStarted,
	ETS_InProgress,
	ETS_Completed,
	ETS_Unavailable
};

UENUM()
enum ETaskType {
	ETT_Fetch,
	ETT_Combat,
	ETT_Escort,
	ETT_Visit,
	ETT_Unavailable
};

USTRUCT(BlueprintType)
struct FTaskStruct {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName TaskId;

	UPROPERTY(BlueprintReadOnly)
	FString Title;
	
	UPROPERTY(BlueprintReadOnly)
	FString Description;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ETaskStatus> Status;
	
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ETaskType> Type;
};
/**
 * 
 */
UCLASS()
class TASKSYSTEM_API UTaskManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
	class UDataTable* TaskDataTable;

	// Task List
	UPROPERTY(VisibleAnywhere, Category="Task")
	TArray<FTaskStruct> TaskList;

	// Current Task
	UPROPERTY(VisibleAnywhere, Category="Task")
	FTaskStruct CurrentTask;

	// Is Current Task Completed
	UPROPERTY(VisibleAnywhere, Category = "Task")
	bool bIsTaskCompleted;

public:

	UTaskManagerSubsystem();

	UFUNCTION(BlueprintCallable)
	TArray<FTaskStruct> GetTaskList();

	UFUNCTION(BlueprintCallable)
	FTaskStruct GetCurrentTask();

	UFUNCTION(BlueprintCallable)
	void SetCurrentTask(FName TaskId);

	UFUNCTION(BlueprintCallable)
	ETaskStatus GetTaskStatus(FName TaskId);

	UFUNCTION(BlueprintCallable)
	ETaskType GetTaskType(FName TaskId);
};
