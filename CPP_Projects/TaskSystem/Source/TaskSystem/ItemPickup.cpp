// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "TaskManagerSubsystem.h"
#include "TSGameInstance.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	TriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(GetRootComponent());

	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(TriggerVolume);
}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AItemPickup::OnComponentBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AItemPickup::OnComponentEndOverlap);
}

// Called every frame
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Will use for rotation
}

void AItemPickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin on AItemPickup"));

	
	UTaskManagerSubsystem* TaskManager = GetGameInstance()->GetSubsystem<UTaskManagerSubsystem>();

	FTaskStruct CurrentTask = TaskManager->GetCurrentTask();

	if (SweepResult.GetActor() != nullptr)
	{
		if (CurrentTask.FetchItemTypes.Contains(SweepResult.GetActor()->GetClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is part of FetchItemTypes of current task."), *SweepResult.GetActor()->GetClass()->GetName())
			TaskManager->IncrementCurrentItemCount();
			Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is not part of FetchItemTypes of current task."), *SweepResult.GetActor()->GetClass()->GetName())
		}
	}
}

void AItemPickup::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End on AItemPickup"));
}