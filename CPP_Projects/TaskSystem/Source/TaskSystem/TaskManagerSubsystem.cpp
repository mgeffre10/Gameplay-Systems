// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManagerSubsystem.h"
#include "TSGameInstance.h"

void UTaskManagerSubsystem::SetTaskDataTable(UDataTable* DataTable)
{
	TaskDataTable = DataTable;
}

TArray<FName> UTaskManagerSubsystem::GetTaskList()
{
	return TaskDataTable->GetRowNames();
}

void UTaskManagerSubsystem::UpdateTaskList(FName TaskName, FTaskStruct UpdatedTask)
{
	for (auto iter : TaskDataTable->GetRowMap())
	{
		if (iter.Key == TaskName)
		{
			FTaskStruct* Task = (FTaskStruct*)iter.Value;
			Task = &UpdatedTask;
		}
	}
}

FTaskStruct UTaskManagerSubsystem::GetCurrentTask()
{
	return CurrentTask;
}

ETaskStatus UTaskManagerSubsystem::GetTaskStatus(FName Task)
{
	if (TaskDataTable->GetRowMap().Contains(Task))
	{
		return TaskDataTable->FindRow<FTaskStruct>(Task, ContextString)->Status;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s does not contain task %s"), *ContextString, *Task.ToString());
	return ETaskStatus::ETS_Unavailable;
	
}

ETaskType UTaskManagerSubsystem::GetTaskType(FName Task)
{
	if (TaskDataTable->GetRowMap().Contains(Task))
	{
		return TaskDataTable->FindRow<FTaskStruct>(Task, ContextString)->Type;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s does not contain task %s"), *ContextString, *Task.ToString());
	return ETaskType::ETT_Unavailable;
}

void UTaskManagerSubsystem::IncrementCurrentItemCount()
{
	CurrentTask.CurrentItemCount++;
	Cast<UTSGameInstance>(GetGameInstance())->UpdateCurrentTaskWidget(CurrentTask);
	CheckIfTaskComplete();
}

void UTaskManagerSubsystem::CheckIfTaskComplete()
{
	if (CurrentTask.CurrentItemCount == CurrentTask.ItemRequirementCount)
	{
		CurrentTask.Status = ETaskStatus::ETS_Completed;
	}
}

void UTaskManagerSubsystem::GetNextTask()
{
	if (CurrentTask.Status == ETaskStatus::ETS_Completed || CurrentTask.Title.IsEmpty())
	{
		if (CurrentTask.Status == ETaskStatus::ETS_Completed)
		{
			UpdateTaskList(CurrentTaskName, CurrentTask);
		}

		for (auto iter : TaskDataTable->GetRowMap())
		{
			FTaskStruct Task = *(FTaskStruct*)iter.Value;

			if (Task.Status == ETaskStatus::ETS_NotStarted && iter.Key != CurrentTaskName)
			{
				CurrentTask = Task;
				CurrentTaskName = iter.Key;
				return;
			}
		}
	}
}