// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaskGiver.generated.h"

UCLASS()
class TASKSYSTEM_API ATaskGiver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskGiver();

	//Trigger Volume
	UPROPERTY(VisibleAnywhere, Category = "Overlap")
	class UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
