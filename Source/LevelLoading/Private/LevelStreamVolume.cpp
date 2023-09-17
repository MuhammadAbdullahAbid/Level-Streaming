// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamVolume.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelStreamVolume::ALevelStreamVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsLoadStarted = false;
	bIsLevelLoaded = false;
	LoadPercent = 0.0f;

}

// Called when the game starts or when spawned
void ALevelStreamVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelStreamVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsLoadStarted)
	{
		if (LoadPercent <= 100.0f)
		{
			LoadPercent = LoadPercent + (DeltaTime*50);
			UE_LOG(LogTemp, Warning, TEXT("Load Percentage : %f"), LoadPercent);
			OnLevelLoading.Broadcast(LoadPercent);

			if (bIsLevelLoaded)
			{
				LoadPercent = LoadPercent + (DeltaTime * 80);
				//OnLevelLoading.Broadcast(LoadPercent);
			}
	
		}
		else
		{
			bIsLoadStarted = false;
			OnLoadComplete.Broadcast();
		}

	}

}

void ALevelStreamVolume::LoadLevel(FName LevelName, FVector ActorLocation)
{
	UGameplayStatics::LoadStreamLevel(this, LevelName, true, false, LatentInfo);
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->SetActorLocation(ActorLocation);
}

void ALevelStreamVolume::UnLoadLevel(FName LevelName)
{
	UGameplayStatics::UnloadStreamLevel(this, LevelName, LatentInfo, false);
}

bool ALevelStreamVolume::IsLevelLoaded(FName LevelName)
{
	LevelStreaming = UGameplayStatics::GetStreamingLevel(this, LevelName);
	if (LevelStreaming)
	{
		return LevelStreaming->IsLevelLoaded();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Loaded"));
		return true;
	}
}
