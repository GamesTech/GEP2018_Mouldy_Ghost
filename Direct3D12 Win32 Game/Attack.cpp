#include "pch.h"
#include "Attack.h"
#include <fstream>

Attack::Attack(std::string _attack_file)
{
	std::ifstream attack_file;
	attack_file.open("\\GameAssets\\Characers\\Attacks\\" + _attack_file);
	attack_file.close();
}

void Attack::SetUpAttack(std::string _attack_file)
{
}