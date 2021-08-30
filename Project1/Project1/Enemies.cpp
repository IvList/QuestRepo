//Enemies.cpp - Call enemy stats.

#include <stdio.h>
#include "Enemies.h"

void EnemyActions::EnemyInfo(Monsters name) //Shows stats for chosen enemy
{
	printf("Name - %s.\n", Enemies[name]->Name);
	printf("LVL - %d.\n", Enemies[name]->LVL);
	printf("HP - %d.\n", Enemies[name]->HP);
	printf("ATK - %d.\n", Enemies[name]->ATK);
	printf("MAG - %d.\n", Enemies[name]->MAG);
	printf("DEF - %d.\n", Enemies[name]->DEF);
	printf("MDEF - %d.\n", Enemies[name]->MDEF);
	printf("EXPReward - %d.\n", Enemies[name]->EXPReward); //comment that one after test
	if (Enemies[name]->PrefATK)
	{
		printf("Enemy attacks are magical.\n");
	}
	else
	{
		printf("Enemy attacks are physical.\n");
	}
}

//Enemy Enemy::ReturnEnemy(int name)
//{
//	return *Enemies[name];
//}

int EnemyActions::returnMStats(int name, int StatN)
{
	int* stats[7] = { &Enemies[name]->HP, &Enemies[name]->ATK, &Enemies[name]->MAG, &Enemies[name]->DEF, &Enemies[name]->MDEF, 0, &Enemies[name]->EXPReward };
	return *stats[StatN];
}

bool EnemyActions::returnBool(int name)
{
	return Enemies[name]->PrefATK;
}