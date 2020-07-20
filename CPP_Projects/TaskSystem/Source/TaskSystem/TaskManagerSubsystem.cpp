// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManagerSubsystem.h"

TArray<FTaskStruct> UTaskManagerSubsystem::GetTaskList()
{
	return TaskList;
}

FTaskStruct UTaskManagerSubsystem::GetCurrentTask()
{
	return CurrentTask;
}

void UTaskManagerSubsystem::SetCurrentTask(FName TaskId)
{
	for (FTaskStruct Task : TaskList)
	{
		if (Task.TaskId == TaskId)
		{
			CurrentTask = Task;
			return;
		}
	}
}

ETaskStatus UTaskManagerSubsystem::GetTaskStatus(FName TaskId)
{
	for (FTaskStruct Task : TaskList)
	{
		if (Task.TaskId == TaskId)
		{
			return Task.Status;
		}
	}

	return ETaskStatus::ETS_Unavailable;
}

ETaskType UTaskManagerSubsystem::GetTaskType(FName TaskId)
{
	for (FTaskStruct Task : TaskList)
	{
		if (Task.TaskId == TaskId)
		{
			return Task.Type;
		}
	}

	return ETaskType::ETT_Unavailable;
}