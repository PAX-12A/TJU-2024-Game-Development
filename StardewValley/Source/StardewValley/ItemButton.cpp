/*****************************************************************//**
 * \file   ItemButton.cpp
 * \brief  To pass parameter on event
 * 
 * \author 4_of_Diamonds
 * \date   December 2024
 *********************************************************************/

#include "ItemButton.h"
#include "EventSystem.h"

UItemButton::UItemButton()
{
	OnClicked.AddDynamic(this, &UItemButton::OnClick);
}

void UItemButton::OnClick()
{
	FString name = GetName();
	bool is_shortcut = false;
	if (name.Len() >= 11 && "BtnShortcut" == name.Left(11))
	{
		is_shortcut = true;
	}
	int32 id = 0;
	for (int32 i = 0; i < name.Len(); i++)
	{
		if (name[i] < '0' || name[i] > '9')continue;
			id = id * 10 + name[i] - '0';
	}
	if (!is_shortcut)OnItemSelected.Broadcast(id);
	else OnShortcutSelected.Broadcast(id);
}