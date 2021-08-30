//Test.cpp - Functions to test performance of certain elements of the project.
#include <stdio.h>
#include "MChar.h"
#include "Enemies.h"
#include "Test.h"

void Test::GeneralCheck()
{
    MainCharActions::NameChar();
    MainCharActions::StatChange(3, 1, 1);
    MainCharActions::CharInfo();
    MainCharActions::ExpIncrease(102);
    MainCharActions::LvlUpCheck();
    MainCharActions::ExpIncrease(102);
    MainCharActions::ExpIncrease(102);
    MainCharActions::LvlUpCheck();
    MainCharActions::CharInfo();
	EnemyActions::EnemyInfo(GOBLIN);
	EnemyActions::EnemyInfo(GOBLIN_SHAMAN);
	EnemyActions::EnemyInfo(TROLL);
}

void Test::MCharCheck()
{
    MainCharActions::NameChar();
    MainCharActions::StatChange(3, 1, 1);
    MainCharActions::CharInfo();
    MainCharActions::ExpIncrease(102);
    MainCharActions::LvlUpCheck();
    MainCharActions::ExpIncrease(102);
    MainCharActions::ExpIncrease(102);
    MainCharActions::LvlUpCheck();
    MainCharActions::CharInfo();
}

void Test::EnemyCheck()
{
    EnemyActions::EnemyInfo(GOBLIN);
    EnemyActions::EnemyInfo(GOBLIN_SHAMAN);
    EnemyActions::EnemyInfo(TROLL);
}