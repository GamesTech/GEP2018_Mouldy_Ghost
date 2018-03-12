#pragma once
#include "Attack.h"

class MeleeAttack
	:public Attack
{
public:
	MeleeAttack(std::string _attack_file);
	~MeleeAttack() = default;
};