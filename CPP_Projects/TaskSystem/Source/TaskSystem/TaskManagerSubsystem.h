// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ItemPickup.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "TaskManagerSubsystem.generated.h"

UENUM(BlueprintType)
enum ETaskStatus {
	ETS_NotStarted		UMETA(DisplayName = "Not Started"),
	ETS_InProgress		UMETA(DisplayName = "In Progress"),
	ETS_Completed		UMETA(DisplayName = "Completed"),
	ETS_Unavailable		UMETA(DisplayName = "Unavailable")
};

UENUM(BlueprintType)
enum ETaskType {
	ETT_Fetch			UMETA(DisplayName = "Fetch"),
	ETT_Combat			UMETA(DisplayName = "Combat"),
	ETT_Escort			UMETA(DisplayName = "Escort"),
	ETT_Visit			UMETA(DisplayName = "Visit"),
	ETT_Unavailable		UMETA(DisplayName = "Unavailable")
};

USTRUCT(BlueprintType)
struct FTaskStruct : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETaskStatus> Status;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETaskType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Type == ETaskType::ETT_Fetch"))
	TArray< TSubclassOf<AItemPickup> > FetchItemTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Type == ETaskType::ETT_Combat"))
	TArray< TSubclassOf<AEnemy> > EnemyTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Type == ETaskType::ETT_Combat || Type == ETaskType::ETT_Fetch"))
	int ItemRequirementCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Type == ETaskType::ETT_Combat || Type == ETaskType::ETT_Fetch"))
	int CurrentItemCount;
};

/**
 * 
 */
UCLASS()
class TASKSYSTEM_API UTaskManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, Category = "Task")
	class UDataTable* TaskDataTable;

	// Task List
	UPROPERTY(VisibleAnywhere, Category = "Task")
	TArray<FTaskStruct> TaskList;

	// Current Task
	UPROPERTY(VisibleAnywhere, Category = "Task")
	FTaskStruct CurrentTask;

	UPROPERTY(VisibleAnywhere, Category = "Task")
	FName CurrentTaskName;

	// Is Current Task Completed
	UPROPERTY(VisibleAnywhere, Category = "Task")
	bool bIsTaskCompleted;

	UFUNCTION(BlueprintCallable)
	void SetTaskDataTable(UDataTable* DataTable);

	UFUNCTION(BlueprintCallable)
	TArray<FName> GetTaskList();

	UFUNCTION(BlueprintCallable)
	void UpdateTaskList(FName TaskToUpdate, FTaskStruct Task);

	UFUNCTION(BlueprintCallable)
	FTaskStruct GetCurrentTask();

	UFUNCTION(BlueprintCallable)
	ETaskStatus GetTaskStatus(FName Task);

	UFUNCTION(BlueprintCallable)
	ETaskType GetTaskType(FName Task);

	UFUNCTION(BlueprintCallable)
	void IncrementCurrentItemCount();

	UFUNCTION(BlueprintCallable)
	void CheckIfTaskComplete();

	UFUNCTION(BlueprintCallable)
	void GetNextTask();

	FString ContextString;
};
