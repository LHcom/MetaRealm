// Fill out your copyright notice in the Description page of Project Settings.


#include "MR_Controller.h"

#include "MetaRealm/MetaRealm.h"

void AMR_Controller::PostInitializeComponents()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostInitializeComponents();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMR_Controller::PostNetInit()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ServerConnection)
			AB_LOG(LogABNetwork, Log, TEXT("Server Connection: %s"), *NetDriver->ServerConnection.GetName());
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
	}
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMR_Controller::BeginPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::BeginPlay();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMR_Controller::MoveToMeetingRoomMap()
{
	ClientTravel("/Game/KSK/Maps/MeetingRoomMap", ETravelType::TRAVEL_Absolute);
}

void AMR_Controller::MoveToMainMap()
{
	ClientTravel("/Game/KHH/KHH_TestMap/KHH_TESTMap", ETravelType::TRAVEL_Absolute);
}
