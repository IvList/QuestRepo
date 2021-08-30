//Enemies.h - Enemy descriptions.
#pragma once

class Enemy
{
public:
	char Name[15];
	int LVL;
	int HP;
	int ATK;
	int MAG;
	int DEF;
	int MDEF;
	int EXPReward;
	bool PrefATK;
	bool Corpse;
	bool Bind;
	//static Enemy ReturnEnemy(int name);
};

static Enemy Goblin = {"Goblin", 1, 2, 1, 0, 0, 0, 100, false, false, false};
static Enemy GoblinShaman = { "Goblin Shaman", 2, 2, 0, 1, 0, 1, 20, true, false, false };
static Enemy Troll = { "Troll", 3, 10, 4, 0, 1, 5, 50, false, false, false };

static Enemy* Enemies[4] = { nullptr, &Goblin, &GoblinShaman, &Troll };

enum Monsters
{
	NOTHING,
	GOBLIN,
	GOBLIN_SHAMAN,
	TROLL
};

struct EnemyActions
{
	static void EnemyInfo(Monsters name);
	//static int returnHP(int name);
	//static int returnHPATK(int name);
	static int returnMStats(int name, int StatN);
	static bool returnBool(int name);
};