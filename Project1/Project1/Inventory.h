//Inventory.h - Inventory item descriptions. To do - add quest items, more consumables.
#pragma once

#define HPPOTION true
#define MPPOTION false

class InventoryItems
{
public:
	int potionHP;
	int potionMP;
};

struct Inventory
{
	static int potionAmount(bool MpHp);
	static void potionAdd(int amount, bool MpHp);
};