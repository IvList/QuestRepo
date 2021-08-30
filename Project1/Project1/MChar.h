//MChar.h - Character and magic description.
#pragma once
class Character
{
public:
	char Name[10];
	int LVL;
	int EXP;
	int HP;
	int MP;
	int ATK;
	int DEF;
	int MDEF;
	int MAG;
};

enum SpellsEnum
{
	FIREBALL,
	BIND,
	FIREBALST
};

struct MainCharActions
{
	static void NameChar();
	static void LvlUpCheck();
	static void CharInfo();
	static void ExpIncrease(int n);
	static void StatChange(int StatN, int OperN, int n);
	static int StatReturn(int StatN);
	static void AchieveReward(int exp);
	static void LearnMagic(SpellsEnum Spell);
};

enum StatsEnum
{
	HP,
	ATK,
	MAG,
	DEF,
	MDEF,
	MP,
	EXPReward,
};

static Character MainChar;

enum Statuses
{
	S_NONE,
	S_BIND
};

class Magic
{
public:
	char Name[10];
	bool Learned;
	Statuses Status;
	int Multiplier;
	int ManaCost;
	int InScrollNum;
};

static Magic FireBall = { "Fireball", false, S_NONE, 3, 4, 0 };
static Magic Bind = { "Bind", false, S_BIND, 1, 3, 1 };
static Magic FireBlast = { "Fireblast", false, S_NONE, 5, 10, 2 };

static Magic* Spells[3] = { &FireBall, &Bind, &FireBlast };
static int spellsNumber = 3;

struct SpellsActions
{
	static int SpellReturn(int num, int Stat);
	static Statuses StatusReturn(int num);
	static bool LearnedReturn(int num);
};
