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
#include "EventSystem.h"
#include "DataSystem.h"

bool UUserInterface::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	item_selected_ = -1;

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
	UButton* BtnReturnTitle = Cast<UButton>(GetWidgetFromName("BtnReturnTitle"));
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
	if (BtnReturnTitle != nullptr)
	{
		BtnReturnTitle->OnClicked.AddDynamic(this, &UUserInterface::ReturnToTitle);
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
	/// Initial data of ProgressBar should be set here.
	/// Initial data of ProgressBar should be set here.
	/// Initial data of ProgressBar should be set here.
	UButton* BtnAexUp = Cast<UButton>(GetWidgetFromName("BtnAexUp"));
	UButton* BtnHoeUp = Cast<UButton>(GetWidgetFromName("BtnHoeUp"));
	UButton* BtnScytheUp = Cast<UButton>(GetWidgetFromName("BtnScytheUp"));
	if (BarAexExp != nullptr && BarAexExp->Percent == 1.0f)BtnAexUp->SetIsEnabled(true);
	else BtnAexUp->SetIsEnabled(false);
	if (BarHoeExp != nullptr && BarHoeExp->Percent == 1.0f)BtnHoeUp->SetIsEnabled(true);
	else BtnHoeUp->SetIsEnabled(false);
	if (BarScytheExp != nullptr && BarScytheExp->Percent == 1.0f)BtnScytheUp->SetIsEnabled(true);
	else BtnScytheUp->SetIsEnabled(false);

	auto GameInstance = GetGameInstance();
	if (GameInstance != nullptr)
	{
		auto EventSystem = GameInstance->GetSubsystem<UEventSystem>();
		if (EventSystem != nullptr)
		{
			EventSystem->OnAnExpBarFull.AddUObject(this, &UUserInterface::EnableALevelUpButton);
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
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetGameInstance()->GetFirstLocalPlayerController()->SetPause(false);
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
void UUserInterface::IncreaseProgressBarValue(UProgressBar* bar, float value)
{
	if (bar != nullptr)
	{
		float current_value = bar->Percent;
		float new_value;
		if (value + current_value > 1.0f)
			bar->SetPercent((new_value = 1.0f));
		else if (value + current_value < 0.0f)
			bar->SetPercent((new_value = 0.0f));
		else
			bar->SetPercent((new_value = value + current_value));
		if (fabs(new_value - 1.0f) < KINDA_SMALL_NUMBER)//If the progress bar is almost full, set the progress bar to 1.0f directly, otherwise the progress bar will be displayed as 1.0f-0.0001f, which will cause the progress bar to jump back and forth.
		{
			bar->SetPercent(1.0f);
			if (bar->GetName() == "BarAexExp" || bar->GetName() == "BarHoeExp" || bar->GetName() == "BarScytheExp")//Exp Bar
			{
				GetGameInstance()->GetSubsystem<UEventSystem>()->OnAnExpBarFull.Broadcast();
			}
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
	IncreaseProgressBarValue(BarAexSkill, 0.1f);
	SetProgressBarValue(BarAexExp, 0.0f);
	BtnAexUp->SetIsEnabled(false);
}
void UUserInterface::HoeLevelUp()
{
	UProgressBar* BarHoeExp = Cast<UProgressBar>(GetWidgetFromName("BarHoeExp"));
	UProgressBar* BarHoeSkill = Cast<UProgressBar>(GetWidgetFromName("BarHoeSkill"));
	UButton* BtnHoeUp = Cast<UButton>(GetWidgetFromName("BtnHoeUp"));
	IncreaseProgressBarValue(BarHoeSkill, 0.1f);
	SetProgressBarValue(BarHoeExp, 0.0f);
	BtnHoeUp->SetIsEnabled(false);
}
void UUserInterface::ScytheLevelUp()
{
	UProgressBar* BarScytheExp = Cast<UProgressBar>(GetWidgetFromName("BarScytheExp"));
	UProgressBar* BarScytheSkill = Cast<UProgressBar>(GetWidgetFromName("BarScytheSkill"));
	UButton* BtnScytheUp = Cast<UButton>(GetWidgetFromName("BtnScytheUp"));
	IncreaseProgressBarValue(BarScytheSkill, 0.1f);
	SetProgressBarValue(BarScytheExp, 0.0f);
	BtnScytheUp->SetIsEnabled(false);
}
void UUserInterface::DEBUGGER()
{
	for (int32 i = 0; i < 66; i++)
		AddItemToBag(i, 1);
}
void UUserInterface::AddItemToBag(int32 id, int32 amount)
{
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