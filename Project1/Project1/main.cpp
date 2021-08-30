#include <stdio.h>
#include "MChar.h"
#include "Enemies.h"
#include "Test.h"
#include "Inventory.h"
#include "BattleSys.h"


int main(void)
{
	//Test::EnemyCheck();
	MainCharActions::NameChar();
	Inventory::potionAdd(2, HPPOTION);
	Inventory::potionAdd(1, MPPOTION);
	MainCharActions::LearnMagic(BIND);
	BattleSystem::Battle(GOBLIN, GOBLIN_SHAMAN, GOBLIN, GOBLIN, 4);
	MainCharActions::AchieveReward(BattleSystem::GetReward());
	MainCharActions::LvlUpCheck();
	MainCharActions::LearnMagic(FIREBALST);
	BattleSystem::Battle(TROLL, GOBLIN_SHAMAN, NOTHING, NOTHING, 2);
	MainCharActions::AchieveReward(BattleSystem::GetReward());
	MainCharActions::LvlUpCheck();
}
