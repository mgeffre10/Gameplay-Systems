// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskGiver.h"
#include "TaskManagerSubsystem.h"
#include "TSGameInstance.h"

#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ATaskGiver::ATaskGiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(GetRootComponent());
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(TriggerVolume);
}

// Called when the game starts or when spawned
void ATaskGiver::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATaskGiver::OnComponentBeginOverlap);

}

void ATaskGiver::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UTaskManagerSubsystem* TaskManager = GetGameInstance()->GetSubsystem<UTaskManagerSubsystem>();

	if (TaskManager->GetCurrentTask().Status == ETaskStatus::ETS_Completed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Task Complete, getting next task"));
		TaskManager->GetNextTask();
		GetGameInstance<UTSGameInstance>()->UpdateCurrentTaskWidget(TaskManager->GetCurrentTask());
	}
	
} 