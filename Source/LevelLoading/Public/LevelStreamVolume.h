// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/LevelStreaming.h"
#include "LevelStreamVolume.generated.h"

class ULevelStreaming;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelLoading, const float&, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadComplete);
UCLASS()
class LEVELLOADING_API ALevelStreamVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelStreamVolume();

	ULevelStreaming* LevelStreaming;
	FLatentActionInfo LatentInfo;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsLoadStarted;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsLevelLoaded;
	UPROPERTY()
	float LoadPercent;

	UFUNCTION(BlueprintCallable)
	void LoadLevel(FName LevelName, FVector ActorLocation);
	UFUNCTION(BlueprintCallable)
	void UnLoadLevel(FName LevelName);
	UFUNCTION(BlueprintCallable)
	bool IsLevelLoaded(FName LevelName);

	UPROPERTY(BlueprintAssignable, Category = "Level Streaming")
	FOnLevelLoading OnLevelLoading;
	UPROPERTY(BlueprintAssignable, Category = "Level Streaming")
	FOnLoadComplete OnLoadComplete;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
