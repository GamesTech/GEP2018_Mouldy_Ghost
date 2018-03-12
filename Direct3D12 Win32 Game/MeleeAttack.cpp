#include "pch.h"
#include "MeleeAttack.h"
#include <fstream>

MeleeAttack::MeleeAttack(std::string _attack_file)
{
	std::ifstream attack_file;
	attack_file.open("\\GameAssets\\Characers\\Attacks\\" + _attack_file);
	attack_file.close();
}
