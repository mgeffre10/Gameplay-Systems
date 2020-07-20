// Fill out your copyright notice in the Description page of Project Settings.


#include "TSGameInstance.h"

void UTSGameInstance::Init()
{
	FTaskStruct FirstTask = *TaskSystem->GetTaskList().GetData();
	TaskSystem->SetCurrentTask(FirstTask.TaskId);
}

UTaskManagerSubsystem* UTSGameInstance::GetTaskSystem()
{
	return TaskSystem;
}