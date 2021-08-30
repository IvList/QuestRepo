//Inventory.cpp - Manipulations with inventory items.

#include "Inventory.h"

InventoryItems CharInventory = { 2, 1 };

void Inventory::potionAdd(int amount, bool MpHp)
{
	if (MpHp)
	{
		CharInventory.potionHP += amount;
	}
	else
	{
		CharInventory.potionMP += amount;
	}
}

int Inventory::potionAmount(bool MpHp)
{
	if (MpHp)
	{
		return CharInventory.potionHP;
	}
	else 
	{
		return CharInventory.potionMP;
	}
}