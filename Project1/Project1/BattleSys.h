//BattleSys.h - Dummies and Scrolls initialization.
#pragma once

static Character MCharDummy;

static Enemy Dummy1;
static Enemy Dummy2;
static Enemy Dummy3;
static Enemy Dummy4;

static Enemy* Dummies[4] = { &Dummy1, &Dummy2, &Dummy3, &Dummy4 };

static Magic Scroll1;
static Magic Scroll2;
static Magic Scroll3;
static Magic Scroll4;
static Magic Scroll5;
static Magic Scroll6;
static Magic Scroll7;
static Magic Scroll8;
static Magic Scroll9;
static Magic Scroll10;

static Magic* Scrolls[10] = { &Scroll1, &Scroll2, &Scroll3, &Scroll4, &Scroll5, &Scroll6, &Scroll7, &Scroll8, &Scroll9, &Scroll10 };

enum DummiesEnum
{
	DUMMY1,
	DUMMY2,
	DUMMY3,
	DUMMY4
};

struct BattleSystem
{
	static void Battle(Monsters name1, Monsters name2, Monsters name3, Monsters name4, int EnemyN);
	static int GetReward();
};
