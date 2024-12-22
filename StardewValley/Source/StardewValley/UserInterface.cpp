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
#include "ItemButton.h"
#include "Components/ProgressBar.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Image.h"
#include "Components/BrushComponent.h"
#include "Components/CanvasPanel.h"
#include "Engine/Texture2D.h"
#include "SlateBasics.h"
#include "SlateCore.h"
#include "Engine/DataTable.h"
#include "Struct_ItemBase.h"
#include "Engine/StreamableManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EventSystem.h"
#include "DataSystem.h"

bool UUserInterface::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	item_selected_ = -1;
	ChangeToSystem();
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
		BtnBag->OnClicked.AddDynamic(this, &UUserInterface::OnItemDeselected);
	}
	if (BtnPlayer != nullptr)
	{
		BtnPlayer->OnClicked.AddDynamic(this, &UUserInterface::ChangeToPlayer);
		BtnPlayer->OnClicked.AddDynamic(this, &UUserInterface::OnItemDeselected);
	}
	if (BtnSocial != nullptr)
	{
		BtnSocial->OnClicked.AddDynamic(this, &UUserInterface::ChangeToSocial);
		BtnSocial->OnClicked.AddDynamic(this, &UUserInterface::OnItemDeselected);
	}
	if (BtnCraft != nullptr)
	{
		BtnCraft->OnClicked.AddDynamic(this, &UUserInterface::ChangeToCraft);
		BtnCraft->OnClicked.AddDynamic(this, &UUserInterface::OnItemDeselected);
	}
	if (BtnSystem != nullptr)
	{
		BtnSystem->OnClicked.AddDynamic(this, &UUserInterface::ChangeToSystem);
		BtnSystem->OnClicked.AddDynamic(this, &UUserInterface::OnItemDeselected);
	}
	if (BtnDebug != nullptr)
	{
		BtnDebug->OnClicked.AddDynamic(this, &UUserInterface::ChangeToDebug);
		BtnDebug->OnClicked.AddDynamic(this, &UUserInterface::OnItemDeselected);
	}

	/*--------------------------------System Panel---------------------------------*/
	UButton* BtnExit = Cast<UButton>(GetWidgetFromName("BtnExit"));
	UButton* BtnSaveGame = Cast<UButton>(GetWidgetFromName("BtnSaveGame"));
	UButton* BtnReturnToGame = Cast<UButton>(GetWidgetFromName("BtnReturnToGame"));
	UButton* BtnGoodbyeWorld = Cast<UButton>(GetWidgetFromName("BtnGoodbyeWorld"));
	UButton* BtnOptioin = Cast<UButton>(GetWidgetFromName("BtnOption"));
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
	if (BtnGoodbyeWorld != nullptr)
	{
		BtnGoodbyeWorld->OnClicked.AddDynamic(this, &UUserInterface::GoodbyeWorld);
	}
	if (BtnOptioin != nullptr)
	{
		BtnOptioin->OnClicked.AddDynamic(this, &UUserInterface::ConfigOption);
	}

	/*--------------------------------Player Panel---------------------------------*/
	UProgressBar* BarAexSkill = Cast<UProgressBar>(GetWidgetFromName("BarAexSkill"));//Axe is wrongly spelled, but don't mind.
	UProgressBar* BarAexExp = Cast<UProgressBar>(GetWidgetFromName("BarAexExp"));
	UProgressBar* BarHoeSkill = Cast<UProgressBar>(GetWidgetFromName("BarHoeSkill"));
	UProgressBar* BarHoeExp = Cast<UProgressBar>(GetWidgetFromName("BarHoeExp"));
	UProgressBar* BarScytheSkill = Cast<UProgressBar>(GetWidgetFromName("BarScytheSkill"));
	UProgressBar* BarScytheExp = Cast<UProgressBar>(GetWidgetFromName("BarScytheExp"));
	if (GetGameInstance() != nullptr && GetGameInstance()->GetSubsystem<UDataSystem>() != nullptr)
	{
		SetProgressBarValue(BarAexExp, static_cast<float>(GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_axe_exp()) / kMaxExpForEachLevel);
		SetProgressBarValue(BarHoeExp, static_cast<float>(GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_hoe_exp()) / kMaxExpForEachLevel);
		SetProgressBarValue(BarScytheExp, static_cast<float>(GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_scythe_exp()) / kMaxExpForEachLevel);
		SetProgressBarValue(BarAexSkill, static_cast<float>(GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_axe_level()) / kMaxLevel);
		SetProgressBarValue(BarHoeSkill, static_cast<float>(GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_hoe_level()) / kMaxLevel);
		SetProgressBarValue(BarScytheSkill, static_cast<float>(GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_scythe_level()) / kMaxLevel);
		int32 level = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_axe_level();
		if (level != 0)
		{
			FString addr = "/Game/Asset/Icon/Ico_Item_Aex_Level" + FString::FromInt(level) + ".Ico_Item_Aex_Level" + FString::FromInt(level);
			UTexture2D* texture2d = LoadObject<UTexture2D>(nullptr, addr.GetCharArray().GetData());
			UImage* axe_icon = Cast<UImage>(GetWidgetFromName("ImgAxeLevel"));
			FSlateBrush brush;
			brush.SetResourceObject(texture2d);
			axe_icon->SetBrush(brush);
		}
		level = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_hoe_level();
		if (level != 0)
		{
			FString addr = "/Game/Asset/Icon/Ico_Item_Hoe_Level" + FString::FromInt(level) + ".Ico_Item_Hoe_Level" + FString::FromInt(level);
			UTexture2D* texture2d = LoadObject<UTexture2D>(nullptr, addr.GetCharArray().GetData());
			UImage* hoe_icon = Cast<UImage>(GetWidgetFromName("ImgHoeLevel"));
			FSlateBrush brush;
			brush.SetResourceObject(texture2d);
			hoe_icon->SetBrush(brush);
		}
		level = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_scythe_level();
		if (level != 0)
		{
			FString addr = "/Game/Asset/Icon/Ico_Item_Scythe_Level" + FString::FromInt(level) + ".Ico_Item_Scythe_Level" + FString::FromInt(level);
			UTexture2D* texture2d = LoadObject<UTexture2D>(nullptr, addr.GetCharArray().GetData());
			UImage* scythe_icon = Cast<UImage>(GetWidgetFromName("ImgScytheLevel"));
			FSlateBrush brush;
			brush.SetResourceObject(texture2d);
			scythe_icon->SetBrush(brush);
		}
	}
	UButton* BtnAexUp = Cast<UButton>(GetWidgetFromName("BtnAexUp"));
	UButton* BtnHoeUp = Cast<UButton>(GetWidgetFromName("BtnHoeUp"));
	UButton* BtnScytheUp = Cast<UButton>(GetWidgetFromName("BtnScytheUp"));
	if (BarAexExp != nullptr && BarAexExp->Percent == 1.0f && fabs(BarAexSkill->Percent - 1.0f) > KINDA_SMALL_NUMBER)BtnAexUp->SetIsEnabled(true);
	else BtnAexUp->SetIsEnabled(false);
	if (BarHoeExp != nullptr && BarHoeExp->Percent == 1.0f && fabs(BarHoeSkill->Percent - 1.0f) > KINDA_SMALL_NUMBER)BtnHoeUp->SetIsEnabled(true);
	else BtnHoeUp->SetIsEnabled(false);
	if (BarScytheExp != nullptr && BarScytheExp->Percent == 1.0f && fabs(BarScytheSkill->Percent - 1.0f) > KINDA_SMALL_NUMBER)BtnScytheUp->SetIsEnabled(true);
	else BtnScytheUp->SetIsEnabled(false);

	auto GameInstance = GetGameInstance();
	if (GameInstance != nullptr)
	{
		auto EventSystem = GameInstance->GetSubsystem<UEventSystem>();
		if (EventSystem != nullptr)
		{
			EventSystem->OnAnExpBarFull.AddUObject(this, &UUserInterface::EnableALevelUpButton);
			EventSystem->OnSkillExpUpdate.AddUObject(this, &UUserInterface::ExpGiver);
		}
	}
	BtnAexUp->OnClicked.AddDynamic(this, &UUserInterface::AxeLevelUp);
	BtnHoeUp->OnClicked.AddDynamic(this, &UUserInterface::HoeLevelUp);
	BtnScytheUp->OnClicked.AddDynamic(this, &UUserInterface::ScytheLevelUp);
	/*--------------------------------Bag Panel---------------------------------*/
	for (int32 i = 1; i <= 10; ++i)
	{
		FString ButtonName = FString::Printf(TEXT("BtnShortcut_%d"), i);
		UItemButton* BtnShortcut = Cast<UItemButton>(GetWidgetFromName(*ButtonName));

		if (BtnShortcut)
		{
			BtnShortcut->OnShortcutSelected.AddUObject(this, &UUserInterface::OnShortcutSelected);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Button %s not found or is nullptr"), *ButtonName);
		}
	}
	if (GetGameInstance() != nullptr && GetGameInstance()->GetSubsystem<UDataSystem>() != nullptr)
	{
		for (auto item : GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_bag())
		{
			AddItemToBag(item.Key, item.Value);
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(item.Key, -1 * item.Value);
		}
		if (GetGameInstance()->GetSubsystem<UEventSystem>() != nullptr)
		{
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnGivenItems.AddUObject(this, &UUserInterface::AddItemToBag);
		}
	}

	/*--------------------------------Debug Panel---------------------------------*/
	UButton* Debugger = Cast<UButton>(GetWidgetFromName("Debugger"));
	if (Debugger != nullptr)
	{
		Debugger->OnClicked.AddDynamic(this, &UUserInterface::DEBUGGER);
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
	//GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetGameInstance()->GetFirstLocalPlayerController()->SetPause(false);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnUIMenuClosed.Broadcast();
	RemoveFromParent();
}
void UUserInterface::GoodbyeWorld()
{
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnReturnTitle.Broadcast();
	auto GetSaveGameFilePath = [](const FString& SlotName) -> FString
		{
			FString SaveDirectory = FPaths::ProjectSavedDir() / TEXT("SaveGames");

			FString SaveGameFileName = SlotName + TEXT(".sav");
			FString SaveGameFilePath = SaveDirectory / SaveGameFileName;

			return SaveGameFilePath;
		};
	FString SaveGameFilePath = GetSaveGameFilePath("SavedGame");
	UE_LOG(LogTemp, Warning, TEXT("address : %s"), *SaveGameFilePath);

	if (IFileManager::Get().FileExists(*SaveGameFilePath))
	{
		bool bSuccess = IFileManager::Get().Delete(*SaveGameFilePath);
		UE_LOG(LogTemp, Warning, TEXT("Delete : %d"), bSuccess);
	}
	GetGameInstance()->GetSubsystem<UDataSystem>()->do_save = false;
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
void UUserInterface::ConfigOption()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Developing..."));
}
void UUserInterface::IncreaseProgressBarValue(UProgressBar* bar, float value)
{
	if (bar != nullptr)
	{
		float current_value = bar->Percent;
		if (fabs(current_value - 1.0f) < KINDA_SMALL_NUMBER) return;
		float new_value;
		if (value + current_value > 1.0f)
			bar->SetPercent((new_value = 1.0f));
		else if (value + current_value < 0.0f)
			bar->SetPercent((new_value = 0.0f));
		else
			bar->SetPercent((new_value = value + current_value));
		if (fabs(new_value - 1.0f) < KINDA_SMALL_NUMBER)//If the progress bar is almost full, set the progress bar to 1.0f directly, otherwise the progress bar will be displayed as 1.0f-0.0001f, which will cause the progress bar to jump back and forth.
		{
			new_value = 1.0f;
			bar->SetPercent(1.0f);
			if (bar->GetName() == "BarAexExp" || bar->GetName() == "BarHoeExp" || bar->GetName() == "BarScytheExp")//Exp Bar
			{
				GetGameInstance()->GetSubsystem<UEventSystem>()->OnAnExpBarFull.Broadcast();
			}
		}
		
		//Update data system
		if (bar->GetName() == "BarAexExp")
		{
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_player_axe_exp(static_cast<int32>(new_value * kMaxExpForEachLevel));
		}
		else if (bar->GetName() == "BarHoeExp")
		{
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_player_hoe_exp(static_cast<int32>(new_value * kMaxExpForEachLevel));
		}
		else if (bar->GetName() == "BarScytheExp")
		{
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_player_scythe_exp(static_cast<int32>(new_value * kMaxExpForEachLevel));
		}
	}
}
void UUserInterface::SetProgressBarValue(UProgressBar* bar, float value)
{
	if (bar != nullptr && value >= 0.0f && value <= 1.0f)
	{
		bar->SetPercent(value);
	}
}
void UUserInterface::EnableALevelUpButton()
{
	UProgressBar* BarAexExp = Cast<UProgressBar>(GetWidgetFromName("BarAexExp"));
	UProgressBar* BarHoeExp = Cast<UProgressBar>(GetWidgetFromName("BarHoeExp"));
	UProgressBar* BarScytheExp = Cast<UProgressBar>(GetWidgetFromName("BarScytheExp"));
	UProgressBar* BarAexSkill = Cast<UProgressBar>(GetWidgetFromName("BarAexSkill"));
	UProgressBar* BarHoeSkill = Cast<UProgressBar>(GetWidgetFromName("BarHoeSkill"));
	UProgressBar* BarScytheSkill = Cast<UProgressBar>(GetWidgetFromName("BarScytheSkill"));
	UButton* BtnAexUp = Cast<UButton>(GetWidgetFromName("BtnAexUp"));
	UButton* BtnHoeUp = Cast<UButton>(GetWidgetFromName("BtnHoeUp"));
	UButton* BtnScytheUp = Cast<UButton>(GetWidgetFromName("BtnScytheUp"));
	if (BarAexExp != nullptr)
	{
		if (BarAexExp->Percent == 1.0f && fabs(BarAexSkill->Percent - 1.0f) > KINDA_SMALL_NUMBER)
		{
			BtnAexUp->SetIsEnabled(true);
		}
	}
	if (BarHoeExp != nullptr && fabs(BarHoeSkill->Percent - 1.0f) > KINDA_SMALL_NUMBER)
	{
		if (BarHoeExp->Percent == 1.0f)
		{
			BtnHoeUp->SetIsEnabled(true);
		}
	}
	if (BarScytheExp != nullptr && fabs(BarScytheSkill->Percent - 1.0f) > KINDA_SMALL_NUMBER)
	{
		if (BarScytheExp->Percent == 1.0f)
		{
			BtnScytheUp->SetIsEnabled(true);
		}
	}
}
void UUserInterface::AxeLevelUp()
{
	UProgressBar* BarAexExp = Cast<UProgressBar>(GetWidgetFromName("BarAexExp"));
	UProgressBar* BarAexSkill = Cast<UProgressBar>(GetWidgetFromName("BarAexSkill"));
	UButton* BtnAexUp = Cast<UButton>(GetWidgetFromName("BtnAexUp"));
	IncreaseProgressBarValue(BarAexSkill, 0.25f);
	SetProgressBarValue(BarAexExp, 0.0f);
	BtnAexUp->SetIsEnabled(false);

	//Update data system
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_player_axe_level(GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_axe_level() + 1);
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_player_axe_exp(0);

	//Change the icon
	int32 level = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_axe_level();
	FString addr = "/Game/Asset/Icon/Ico_Item_Aex_Level" + FString::FromInt(level) + ".Ico_Item_Aex_Level" + FString::FromInt(level);
	UTexture2D* texture2d = LoadObject<UTexture2D>(nullptr, addr.GetCharArray().GetData());
	UImage* axe_icon = Cast<UImage>(GetWidgetFromName("ImgAxeLevel"));
	FSlateBrush brush;
	brush.SetResourceObject(texture2d);
	axe_icon->SetBrush(brush);
}
void UUserInterface::HoeLevelUp()
{
	UProgressBar* BarHoeExp = Cast<UProgressBar>(GetWidgetFromName("BarHoeExp"));
	UProgressBar* BarHoeSkill = Cast<UProgressBar>(GetWidgetFromName("BarHoeSkill"));
	UButton* BtnHoeUp = Cast<UButton>(GetWidgetFromName("BtnHoeUp"));
	IncreaseProgressBarValue(BarHoeSkill, 0.25f);
	SetProgressBarValue(BarHoeExp, 0.0f);
	BtnHoeUp->SetIsEnabled(false);

	//Update data system
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_player_hoe_level(GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_hoe_level() + 1);
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_player_hoe_exp(0);

	//Change the icon
	int32 level = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_hoe_level();
	FString addr = "/Game/Asset/Icon/Ico_Item_Hoe_Level" + FString::FromInt(level) + ".Ico_Item_Hoe_Level" + FString::FromInt(level);
	UTexture2D* texture2d = LoadObject<UTexture2D>(nullptr, addr.GetCharArray().GetData());
	UImage* hoe_icon = Cast<UImage>(GetWidgetFromName("ImgHoeLevel"));
	FSlateBrush brush;
	brush.SetResourceObject(texture2d);
	hoe_icon->SetBrush(brush);
}
void UUserInterface::ScytheLevelUp()
{
	UProgressBar* BarScytheExp = Cast<UProgressBar>(GetWidgetFromName("BarScytheExp"));
	UProgressBar* BarScytheSkill = Cast<UProgressBar>(GetWidgetFromName("BarScytheSkill"));
	UButton* BtnScytheUp = Cast<UButton>(GetWidgetFromName("BtnScytheUp"));
	IncreaseProgressBarValue(BarScytheSkill, 0.25f);
	SetProgressBarValue(BarScytheExp, 0.0f);
	BtnScytheUp->SetIsEnabled(false);

	//Update data system
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_player_scythe_level(GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_scythe_level() + 1);
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_player_scythe_exp(0);

	//Change the icon
	int32 level = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_scythe_level();
	FString addr = "/Game/Asset/Icon/Ico_Item_Scythe_Level" + FString::FromInt(level) + ".Ico_Item_Scythe_Level" + FString::FromInt(level);
	UTexture2D* texture2d = LoadObject<UTexture2D>(nullptr, addr.GetCharArray().GetData());
	UImage* scythe_icon = Cast<UImage>(GetWidgetFromName("ImgScytheLevel"));
	FSlateBrush brush;
	brush.SetResourceObject(texture2d);
	scythe_icon->SetBrush(brush);
}
void UUserInterface::ExpGiver(int32 type, int32 amount)
{
	UE_LOG(LogTemp, Warning, TEXT("ExpGiver"));
	UProgressBar* BarAexExp = Cast<UProgressBar>(GetWidgetFromName("BarAexExp"));
	UProgressBar* BarHoeExp = Cast<UProgressBar>(GetWidgetFromName("BarHoeExp"));
	UProgressBar* BarScytheExp = Cast<UProgressBar>(GetWidgetFromName("BarScytheExp"));
	switch (type)
	{
	case 1:
		IncreaseProgressBarValue(BarAexExp, static_cast<float>(amount) / 100.0f);
		break;
	case 2:
		IncreaseProgressBarValue(BarHoeExp, static_cast<float>(amount) / 100.0f);
		break;
	case 3:
		IncreaseProgressBarValue(BarScytheExp, static_cast<float>(amount) / 100.0f);
		break;
	default:
		break;
	}
}
void UUserInterface::DEBUGGER()
{
	for (int32 i = 0; i < 66; i++)
		AddItemToBag(i, 1);
	UProgressBar* BarAexExp = Cast<UProgressBar>(GetWidgetFromName("BarAexExp"));
	UProgressBar* BarHoeExp = Cast<UProgressBar>(GetWidgetFromName("BarHoeExp"));
	UProgressBar* BarScytheExp = Cast<UProgressBar>(GetWidgetFromName("BarScytheExp"));
	IncreaseProgressBarValue(BarAexExp, 0.2f);
	IncreaseProgressBarValue(BarHoeExp, 0.2f);
	IncreaseProgressBarValue(BarScytheExp, 0.2f);
}
void UUserInterface::AddItemToBag(int32 id, int32 amount)
{
	GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(id, amount);
	if (ItemsInBag.Contains(id))//If the item is already in the bag, increase the amount of the item in the bag
	{
		ItemsInBag[id] += amount;
		FName name = FName("BtnItem" + FString::FromInt(id));
		UItemButton* BtnItem = Cast<UItemButton>(GetWidgetFromName(name));
		if (BtnItem != nullptr)
		{
			FName text_name = FName("TextAmount" + FString::FromInt(id));
			UTextBlock* TextAmount = Cast<UTextBlock>(GetWidgetFromName(text_name));
			if (TextAmount != nullptr)
			{
				TextAmount->SetText(FText::FromString(FString::FromInt(ItemsInBag[id])));
			}
		}
	}
	else//If the item is not in the bag, add the item to the bag
	{
		ItemsInBag.Add(id, amount);

		FName name = FName("BtnItem" + FString::FromInt(id));
		UItemButton* BtnItem = NewObject<UItemButton>(GetWorld(), UItemButton::StaticClass(), name);
		BtnItem->SetRenderScale(FVector2D(3.5f, 2.5f));

		BtnItem->OnItemSelected.AddUObject(this, &UUserInterface::OnItemSelected);

		FName text_name = FName("TextAmount" + FString::FromInt(id));
		UTextBlock* TextAmount = NewObject<UTextBlock>(GetWorld(), UTextBlock::StaticClass(), text_name);
		TextAmount->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f));//Set the color black.
		TextAmount->SetRenderScale(FVector2D(1.0f, 1.0f));
		TextAmount->SetRenderTranslation(FVector2D(0.0f, 14.0f));
		TextAmount->SetText(FText::FromString(FString::FromInt(ItemsInBag[id])));

		UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBase.DT_ItemBase"));
		FStruct_ItemBase* item_info = item_data_table->FindRow<FStruct_ItemBase>(FName(*FString::FromInt(id)), "");
		FName image_name = FName("Image" + FString::FromInt(id));
		UImage* Image = NewObject<UImage>(GetWorld(), UImage::StaticClass(), image_name);
		if (item_info != nullptr)
		{
			UTexture2D* texture = item_info->icon_;
			FSlateBrush brush;
			brush.SetResourceObject(texture);
			Image->SetBrush(brush);
			Image->SetBrushSize(FVector2D(20.0, 30.0));
		}
		else
		{
			UTexture2D* texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Asset/Icon/Ico_Test_4oD.Ico_Test_4oD'"));
			FSlateBrush brush;
			brush.SetResourceObject(texture);
			Image->SetBrush(brush);
			Image->SetBrushSize(FVector2D(20.0, 30.0));
		}

		FName overlay_name = FName("Overlay" + FString::FromInt(id));
		UOverlay* overlay = NewObject<UOverlay>(GetWorld(), UOverlay::StaticClass(), overlay_name);
		overlay->AddChild(BtnItem);
		BtnItem->AddChild(Image);
		overlay->AddChild(TextAmount);

		UWrapBox* ListItemBag = Cast<UWrapBox>(GetWidgetFromName("ListItemBag"));
		if (ListItemBag != nullptr)
		{
			ListItemBag->AddChild(overlay);
		}
	}
}
void UUserInterface::RemoveItemFromBag(int32 id, int32 amount)
{
	if (ItemsInBag.Contains(id))
	{
		int32 left_amount = ItemsInBag[id] - amount;
		if (left_amount <= 0)
		{
			ItemsInBag.Remove(id);
			FName name = FName("Overlay" + FString::FromInt(id));
			UOverlay* overlay = Cast<UOverlay>(GetWidgetFromName(name));
			if (overlay != nullptr)
			{
				overlay->RemoveFromParent();
			}
		}
		else
		{
			ItemsInBag[id] = left_amount;
			FName text_name = FName("TextAmount" + FString::FromInt(id));
			UTextBlock* TextAmount = Cast<UTextBlock>(GetWidgetFromName(text_name));
			if (TextAmount != nullptr)
			{
				TextAmount->SetText(FText::FromString(FString::FromInt(ItemsInBag[id])));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Item (id = %d) is not in the bag, so you cannot remove it"), id);
	}
}
void UUserInterface::OnItemSelected(int32 id)
{
	if (item_selected_ == id)
	{
		OnItemDeselected();
		return;
	}
	if (item_selected_ != -1) OnItemDeselected();
	item_selected_ = id;

	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBase.DT_ItemBase"));
	FStruct_ItemBase* item_info = item_data_table->FindRow<FStruct_ItemBase>(FName(*FString::FromInt(id)), "");

	FName image_icon_name = FName("ImageIcon" + FString::FromInt(id));
	UImage* image_icon = NewObject<UImage>(GetWorld(), UImage::StaticClass(), image_icon_name);
	if (item_info != nullptr)
	{
		UTexture2D* texture = item_info->icon_;
		FSlateBrush brush;
		brush.SetResourceObject(texture);
		image_icon->SetBrush(brush);
		image_icon->SetBrushSize(FVector2D(20.0, 30.0));
	}
	else
	{
		UTexture2D* texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Asset/Icon/Ico_Test_4oD.Ico_Test_4oD'"));
		FSlateBrush brush;
		brush.SetResourceObject(texture);
		image_icon->SetBrush(brush);
		image_icon->SetBrushSize(FVector2D(20.0, 30.0));
	}

	UCanvasPanel* CanvasPanel_0 = Cast<UCanvasPanel>(GetWidgetFromName("CanvasPanel_0"));
	CanvasPanel_0->AddChild(image_icon);
}
void UUserInterface::OnItemDeselected()
{
	if (item_selected_ == -1) return;
	FName image_icon_name = FName("ImageIcon" + FString::FromInt(item_selected_));
	UImage* image_icon = Cast<UImage>(GetWidgetFromName(image_icon_name));
	if (image_icon != nullptr)
	{
		image_icon->RemoveFromParent();
	}
	item_selected_ = -1;
}
void UUserInterface::OnShortcutSelected(int32 index)
{
	FName name = FName("BtnShortcut_" + FString::FromInt(index));
	UItemButton* button = Cast<UItemButton>(GetWidgetFromName(name));
	button->SetRenderTransformPivot(FVector2D(0.0f, 0.0f));
	UImage* image = Cast<UImage>(button->GetChildAt(0));
	if (item_selected_ == -1)
	{
		if (image != nullptr && image->GetName().Left(16) == "ShortcutItemIcon")//Remove it.
		{
			button->SetRenderScale(FVector2D(3.5f, 2.5f));
			UTexture2D* texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Asset/Icon/Ico_Axe_Level1.Ico_Axe_Level1'"));
			FSlateBrush brush;
			brush.SetResourceObject(texture);
			image->SetBrush(brush);
			image->SetBrushSize(FVector2D(20.0, 30.0));

			FString new_name = FString::Printf(TEXT("IcoShortcut_%d"), index);
			const TCHAR* the_new_name = new_name.GetCharArray().GetData();
			image->Rename(the_new_name);

			GetGameInstance()->GetSubsystem<UEventSystem>()->OnItemRemovedFromShortcutBar.Broadcast(index);
		}
	}
	else//Add it.
	{
		button->SetRenderScale(FVector2D(3.5f, 2.5f));
		FString new_name = FString::Printf(TEXT("ShortcutItemIcon%d"), index);
		const TCHAR* the_new_name = new_name.GetCharArray().GetData();
		image->Rename(the_new_name);

		UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBase.DT_ItemBase"));
		FStruct_ItemBase* item_info = item_data_table->FindRow<FStruct_ItemBase>(FName(*FString::FromInt(item_selected_)), "");
		if (item_info != nullptr)
		{
			UTexture2D* texture = item_info->icon_;
			FSlateBrush brush;
			brush.SetResourceObject(texture);
			image->SetBrush(brush);
			image->SetBrushSize(FVector2D(20.0, 30.0));
		}
		else
		{
			UTexture2D* texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Asset/Icon/Ico_Test_4oD.Ico_Test_4oD'"));
			FSlateBrush brush;
			brush.SetResourceObject(texture);
			image->SetBrush(brush);
			image->SetBrushSize(FVector2D(20.0, 30.0));
		}
		GetGameInstance()->GetSubsystem<UEventSystem>()->OnItemAddedToShortcutBar.Broadcast(item_selected_, index);
		OnItemDeselected();
	}
}

void UUserInterface::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (item_selected_ != -1)
	{
		APlayerController* player_controller = GetWorld()->GetFirstPlayerController();

		if (player_controller != nullptr)
		{
			FVector2D MousePosition;
			player_controller->GetMousePosition(MousePosition.X, MousePosition.Y);

			FVector2D LocalPosition = MyGeometry.AbsoluteToLocal(MousePosition);

			UImage* image = Cast<UImage>(GetWidgetFromName(FName("ImageIcon" + FString::FromInt(item_selected_))));
			image->SetRenderTranslation(LocalPosition);
		}
	}
}