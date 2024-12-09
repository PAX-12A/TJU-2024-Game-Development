/*****************************************************************//**
 * \file   UserInterface.cpp
 * \brief  The implementation of the user interface
 *
 * \author 4_of_Diamonds
 * \date   December 2024
 *********************************************************************/

#include "UserInterface.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EventSystem.h"
#include "DataSystem.h"

bool UUserInterface::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/*--------------------------------Change the panel---------------------------------*/
	UButton* BtnBag = Cast<UButton>(GetWidgetFromName("BtnBag"));
	UButton* BtnPlayer = Cast<UButton>(GetWidgetFromName("BtnPlayer"));
	UButton* BtnSocial = Cast<UButton>(GetWidgetFromName("BtnSocial"));
	UButton* BtnCraft = Cast<UButton>(GetWidgetFromName("BtnCraft"));
	UButton* BtnSystem = Cast<UButton>(GetWidgetFromName("BtnSystem"));
	UButton* BtnDebug = Cast<UButton>(GetWidgetFromName("BtnDebug"));
	if (BtnBag != nullptr)
	{
		BtnBag->OnClicked.AddDynamic(this, &UUserInterface::ChangeToBag);
	}
	if (BtnPlayer != nullptr)
	{
		BtnPlayer->OnClicked.AddDynamic(this, &UUserInterface::ChangeToPlayer);
	}
	if (BtnSocial != nullptr)
	{
		BtnSocial->OnClicked.AddDynamic(this, &UUserInterface::ChangeToSocial);
	}
	if (BtnCraft != nullptr)
	{
		BtnCraft->OnClicked.AddDynamic(this, &UUserInterface::ChangeToCraft);
	}
	if (BtnSystem != nullptr)
	{
		BtnSystem->OnClicked.AddDynamic(this, &UUserInterface::ChangeToSystem);
	}
	if (BtnDebug != nullptr)
	{
		BtnDebug->OnClicked.AddDynamic(this, &UUserInterface::ChangeToDebug);
	}

	/*--------------------------------System Panel---------------------------------*/
	UButton* BtnExit = Cast<UButton>(GetWidgetFromName("BtnExit"));
	UButton* BtnSaveGame = Cast<UButton>(GetWidgetFromName("BtnSaveGame"));
	UButton* BtnReturnToGame = Cast<UButton>(GetWidgetFromName("BtnReturnToGame"));
	UButton* BtnReturnTitle = Cast<UButton>(GetWidgetFromName("BtnReturnTitle"));
	UButton* BtnOptioin	= Cast<UButton>(GetWidgetFromName("BtnOption"));
	if (BtnExit != nullptr)
	{
		BtnExit->OnClicked.AddDynamic(this, &UUserInterface::ExitGame);
	}
	if (BtnSaveGame != nullptr)
	{
		BtnSaveGame->OnClicked.AddDynamic(this, &UUserInterface::SaveGame);
	}
	if (BtnReturnToGame != nullptr)
	{
		BtnReturnToGame->OnClicked.AddDynamic(this, &UUserInterface::ReturnToGame);
	}
	if (BtnReturnTitle != nullptr)
	{
		BtnReturnTitle->OnClicked.AddDynamic(this, &UUserInterface::ReturnToTitle);
	}
	if (BtnOptioin != nullptr)
	{
		BtnOptioin->OnClicked.AddDynamic(this, &UUserInterface::ConfigOption);
	}

	return true;
}

void UUserInterface::ChangeInterface(int32 index)
{
	UWidgetSwitcher* Switcher = Cast<UWidgetSwitcher>(GetWidgetFromName("Switcher"));
	if (Switcher != nullptr)
	{
		Switcher->SetActiveWidgetIndex(index);
	}
}
void UUserInterface::ExitGame()
{
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnExitGame.Broadcast();
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
void UUserInterface::SaveGame()
{
	GetGameInstance()->GetSubsystem<UDataSystem>()->SaveGame();
}
void UUserInterface::ReturnToGame()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	RemoveFromParent();
}
void UUserInterface::ReturnToTitle()
{
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnReturnTitle.Broadcast();
}
void UUserInterface::ConfigOption()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Developing..."));
}
