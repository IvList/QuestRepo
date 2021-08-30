//BattleSys.cpp - Describes normal battle mechanics. To do - add more status effects, more interaction with corpses, random ATK numbers.
#include <stdio.h>
#include "MChar.h"
#include "Enemies.h"
#include "BattleSys.h"
#include <cstring>
#include "Inventory.h"

int monsternames[4] = {0, 0, 0, 0};
int EnemyNum = 0;
int rewardEXPpool;
int ScrollsNum;
void MCharATK();

void EnemiesInit(Monsters name1, Monsters name2, Monsters name3, Monsters name4, int EnemyN)
{
	char EnemyParty[100];
	monsternames[0] = name1;
	monsternames[1] = name2;
	monsternames[2] = name3;
	monsternames[3] = name4;
	EnemyNum = EnemyN;
	printf("Fight for your life. Your enemies are");
	strcpy_s(EnemyParty, ": ");
	for (int i = 0; i < EnemyNum; i++)
	{
		strcat_s(EnemyParty, Enemies[monsternames[i]]->Name);
		if(i + 1 < EnemyNum)
		{
			strcat_s(EnemyParty, ", ");
		}
		else
		{
			strcat_s(EnemyParty, ".\n");
		}
	}
	printf(EnemyParty);
}

void CreateMCharDummy()
{
	MCharDummy.ATK = MainCharActions::StatReturn(ATK);
	MCharDummy.DEF = MainCharActions::StatReturn(DEF);
	MCharDummy.MDEF = MainCharActions::StatReturn(MDEF);
	MCharDummy.MAG = MainCharActions::StatReturn(MAG);
	MCharDummy.HP = MainCharActions::StatReturn(HP);
	MCharDummy.MP = MainCharActions::StatReturn(MP);
}

void SpellsInit()
{
	ScrollsNum = 0;
	for (int i = 0; i < spellsNumber; i++)
	{
		if (SpellsActions::LearnedReturn(i))
		{
			Scrolls[ScrollsNum]->Status = SpellsActions::StatusReturn(i);
			Scrolls[ScrollsNum]->Multiplier = SpellsActions::SpellReturn(i, 0);
			Scrolls[ScrollsNum]->ManaCost = SpellsActions::SpellReturn(i, 1);
			Scrolls[ScrollsNum]->InScrollNum = SpellsActions::SpellReturn(i, 2);
			ScrollsNum++;
		}
	}
}

void CreateDummies(Monsters name1, Monsters name2, Monsters name3, Monsters name4, int EnemyN)
{
	CreateMCharDummy();
	EnemiesInit(name1, name2, name3, name4, EnemyN);
	SpellsInit();
	rewardEXPpool = 0;
	for (int i = 0; i < EnemyNum; i++)
	{
		Dummies[i]->HP = EnemyActions::returnMStats(monsternames[i], HP);
		Dummies[i]->ATK = EnemyActions::returnMStats(monsternames[i], ATK);
		Dummies[i]->MAG = EnemyActions::returnMStats(monsternames[i], MAG);
		Dummies[i]->DEF = EnemyActions::returnMStats(monsternames[i], DEF);
		Dummies[i]->MDEF = EnemyActions::returnMStats(monsternames[i], MDEF);
		Dummies[i]->EXPReward = EnemyActions::returnMStats(monsternames[i], EXPReward);
		Dummies[i]->Corpse = false;
		Dummies[i]->Bind = false;
		Dummies[i]->PrefATK = EnemyActions::returnBool(monsternames[i]);
		rewardEXPpool += Dummies[i]->EXPReward;
	}
}

void UseSpell(int ChosenEnemy)
{
	int ChosenSpell;
	printf("Choose spell to use:\n");
	for (int i = 0; i < ScrollsNum; i++)
	{
		printf("%d. %s\n", i + 1, Spells[Scrolls[i]->InScrollNum]->Name);
	}
	scanf_s("%d", &ChosenSpell);
	ChosenSpell--;
	if (Scrolls[ChosenSpell]->ManaCost < MCharDummy.MP)
	{
		MCharDummy.MP -= Scrolls[ChosenSpell]->ManaCost;
		if (Dummies[ChosenEnemy]->Corpse)
		{
			printf("You hit the corpse. Nothing happened.\n");
		}
		else
		{
			int MDMG = MCharDummy.MAG * Scrolls[ChosenSpell]->Multiplier - Dummies[ChosenEnemy]->MDEF;
			if (MDMG < 0) 
			{
				MDMG = 0;
			}
			Dummies[ChosenEnemy]->HP -= MDMG;
			printf("Enemy lost %d HP  and now has %d HP\n", MDMG, Dummies[ChosenEnemy]->HP);
			if (Scrolls[ChosenSpell]->Status == S_BIND)
			{
				Dummies[ChosenEnemy]->Bind = true;
				printf("Enemy was struck by Bind and won't be able to attack for 1 turn.\n");
			}
		}
		printf("Remaining mana - %d.\n", MCharDummy.MP);
	}
	else
	{
		printf("Insufficient mana.\n");
		MCharATK();
	}
}
void UsePotion()
{
	int potion;
	printf("Choose potion:\n");
	printf("1. HP potion. You have %d.\n", Inventory::potionAmount(HPPOTION));
	printf("2. MP potion. You have %d.\n", Inventory::potionAmount(MPPOTION));
	scanf_s("%d", &potion);
	getchar();		//Catching symbols.
	if (potion == 1)
	{
		if (Inventory::potionAmount(HPPOTION) > 0)
		{
			Inventory::potionAdd(-1, HPPOTION);
			MCharDummy.HP += 5;
			printf("5 HP restored.\n");
		}
		else
		{
			printf("No HP potions left.\n");
			MCharATK();
		}
	}
	else if (potion == 2)
	{
		if (Inventory::potionAmount(MPPOTION) > 0)
		{
			Inventory::potionAdd(-1, MPPOTION);
			MCharDummy.MP += 5;
			printf("5 MP restored.\n");
		}
		else
		{
			printf("No MP potions left.\n");
			MCharATK();
		}
	}
}

void MCharATK()
{
	int ChosenEnemy = 0;
	int ChosenATK = 0;
	printf("Choose action:\n");
	printf("1. Attack.\n");
	printf("2. Magic.\n");
	printf("3. Inventory.\n");
	scanf_s("%d", &ChosenATK);
	getchar();		//Catching symbols.
	if (ChosenATK == 3)
	{
		UsePotion();
		return;
	}
	printf("Choose an enemy to attack:\n");
	for (int i = 0; i < EnemyNum; i++)
	{
		if (Dummies[i]->Corpse)
		{
			printf("%d. Corpse\n", i + 1);
		}
		else
		{
			
			printf("%d. %s %d HP", i + 1, Enemies[monsternames[i]]->Name, Dummies[i]->HP);
			if (Dummies[i]->Bind)
			{
				printf("Bound\n");
			}
			else
			{
				printf("\n");
			}
		}
	}
	scanf_s("%d", &ChosenEnemy);
	getchar();		//Catching symbols.
	ChosenEnemy--;
	if (ChosenATK == 1)
	{
		if (Dummies[ChosenEnemy]->Corpse)
		{
			printf("You hit the corpse. Nothing happened.\n");
		}
		else
		{
			int DMG = MCharDummy.ATK - Dummies[ChosenEnemy]->DEF;
			if (DMG < 0)
			{
				DMG = 0;
			}
			Dummies[ChosenEnemy]->HP -= DMG;
			printf("Enemy lost %d HP  and now has %d HP\n", DMG, Dummies[ChosenEnemy]->HP);
		}
	}
	else if (ChosenATK == 2)
	{
		UseSpell(ChosenEnemy);
	}
	if (Dummies[ChosenEnemy]->HP <= 0)
	{
		Dummies[ChosenEnemy]->Corpse = true;
		printf("Enemy died.\n");
	}
}

void EnemyATK(int attacker, bool* atksuccess, bool* playerDead)
{
	*atksuccess = false;
	if (Dummies[attacker]->Corpse || *playerDead)
	{
		return;
	}
	else if(Dummies[attacker]->Bind)
	{
		*atksuccess = true;
		Dummies[attacker]->Bind = false;
		return;
	}
	printf("%s attacks!\n", Enemies[monsternames[attacker]]->Name);
	if (Dummies[attacker]->PrefATK)
	{
		int MDMG = Dummies[attacker]->MAG - MCharDummy.MDEF;
		if(MDMG < 0)
		{
			MDMG = 0;
		}
		MCharDummy.HP -= MDMG;
		printf("You lost %d HP.", MDMG);
	}
	else
	{
		int DMG = Dummies[attacker]->ATK - MCharDummy.DEF;
		if (DMG < 0)
		{
			DMG = 0;
		}
		MCharDummy.HP -= DMG;
		printf("You lost %d HP.", DMG);
	}
	printf("%d HP remaining.\n", MCharDummy.HP);
	*atksuccess = true;
	if (MCharDummy.HP <= 0)
	{
		*playerDead = true;
	}
}

void BattleSystem::Battle(Monsters name1, Monsters name2, Monsters name3, Monsters name4, int EnemyN)
{
	bool enemyATKsuccess = false;
	bool playerDead = false;
	CreateDummies(name1, name2, name3, name4, EnemyN);
	MCharATK();
	while (!playerDead)
	{
		int CorpseCount = EnemyN;
		for (int i = 0; i < EnemyN; i++)
		{
			EnemyATK(i, &enemyATKsuccess, &playerDead);
			if (enemyATKsuccess)
			{
				MCharATK();
			}
			else
			{
				CorpseCount--;
			}
		}
		if (CorpseCount <= 0)
			break;
	}
	if (playerDead)
	{
		printf("You died. Game Over.\n");
	}
	else
	{
		printf("Congratulations! You defeated your enemies and earned %d EXP!\n", rewardEXPpool);
	}
}

int BattleSystem::GetReward()
{
	return rewardEXPpool;
}