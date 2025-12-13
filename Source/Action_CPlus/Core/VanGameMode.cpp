// Fill out your copyright notice in the Description page of Project Settings.


#include "VanGameMode.h"

#include "Action_CPlus/Player/VanPlayerController.h"

AVanGameMode::AVanGameMode()
{
	PlayerControllerClass = AVanPlayerController::StaticClass();
}
