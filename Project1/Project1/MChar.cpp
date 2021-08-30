//MChar.h - Creating character, managing stats.
#include "MChar.h"
#include <stdio.h>

static int LVLCoef = 1; // Each new level will need LVLCoef * LVL more XP to get;

void NewChar()
{
	MainChar.LVL = 1;
	MainChar.EXP = 0;
	MainChar.HP = 15;
	MainChar.MP = 10;
	MainChar.ATK = 2;
	MainChar.DEF = 0;
	MainChar.MDEF = 0;
	MainChar.MAG = 1;
	MainCharActions::LearnMagic(FIREBALL);
}

void MainCharActions::NameChar()
{
	printf("Enter the name of your character.\n");
	scanf_s("%s", MainChar.Name, 10);
	NewChar();
}

void MainCharActions::ExpIncrease(int n)
{
	MainChar.EXP += n;
}

void MainCharActions::StatChange(int StatN, int OperN, int n) //Changes one stat. StatN: 0 - HP, 1 - MP, 2 - ATK, 3 - DEF, 4 - MDEF. OperN: 0 - Subtract, 1 - Add.
{
	int* stats[5] = { &MainChar.HP, &MainChar.MP, &MainChar.ATK, &MainChar.DEF, &MainChar.MDEF };
	if (OperN)
	{
		*stats[StatN] += n;
	}
	else
	{
		*stats[StatN] -= n;
	}
}

int MainCharActions::StatReturn(int StatN)
{
	int* stats[7] = { &MainChar.HP, &MainChar.ATK, &MainChar.MAG, &MainChar.DEF, &MainChar.MDEF, &MainChar.MP, &MainChar.EXP };
	return *stats[StatN];
}

void LvlUp()
{
	MainChar.LVL += 1;
	MainChar.HP += 3;
	MainChar.MP += 2;
	MainChar.ATK += 1;
	MainChar.DEF += 1;
	MainChar.MAG += 1;
	MainChar.MDEF += 1;
	printf("Congratulations! You gained a new level.\n");
	printf("HP increased by 3.\nMP increased by 2.\nATK, MAG, DEF, MDEF increased by 1.\n");
}

void MainCharActions::LvlUpCheck()
{
	if (MainChar.EXP >= 100*LVLCoef)
	{
		MainChar.EXP -= 100*LVLCoef;
		LVLCoef += 2;
		LvlUp();
		MainCharActions::LvlUpCheck();
	}
}

void MainCharActions::CharInfo()
{
	printf("Character name - %s.\n", MainChar.Name);
	printf("Stats:\n");
	printf("LVL - %d.\n", MainChar.LVL);
	printf("EXP - %d.\n", MainChar.EXP);
	printf("HP - %d.\n", MainChar.HP);
	printf("MP - %d.\n", MainChar.MP);
	printf("ATK - %d.\n", MainChar.ATK);
	printf("MAG - %d.\n", MainChar.MAG);
	printf("DEF - %d.\n", MainChar.DEF);
}

void MainCharActions::AchieveReward(int exp)
{
	MainChar.EXP = exp;
}

void MainCharActions::LearnMagic(SpellsEnum Spell)
{
	Spells[Spell]->Learned = true;
}

int SpellsActions::SpellReturn(int num, int Stat)
{
	int* stats[3] = { &Spells[num]->Multiplier, &Spells[num]->ManaCost, &Spells[num]->InScrollNum };
	return *stats[Stat];
}

Statuses SpellsActions::StatusReturn(int num)
{
	return Spells[num]->Status;
}

bool SpellsActions::LearnedReturn(int num)
{
	return Spells[num]->Learned;
}

