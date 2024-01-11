// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyHUD.h"
#include "Blueprint/UserWidget.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (!IsValid(pPlayer0))
		return;

	pPlayer0->SetInputMode(FInputModeUIOnly());
	pPlayer0->bShowMouseCursor = true;
}