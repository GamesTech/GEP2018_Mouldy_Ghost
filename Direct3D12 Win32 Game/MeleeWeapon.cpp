#include "pch.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon()
{
}

MeleeWeapon::MeleeWeapon(RenderData * _RD, std::string _filename, SpawnHandler * _spawner) : Throwable(_RD, _filename, _spawner)
{
}

MeleeWeapon::MeleeWeapon(Item * item_to_copy, RenderData * _RD, string _filename, SpawnHandler * _spawner) : Throwable(item_to_copy, _RD, _filename, _spawner)
{
	MeleeWeapon* melee_ptr = static_cast<MeleeWeapon*>(item_to_copy);

	max_charge = melee_ptr->getMaxCharge();
	on_full_charge = melee_ptr->getOnFullCharge();
	durability = melee_ptr->getDurability();
}

MeleeWeapon::~MeleeWeapon()
{
}

void MeleeWeapon::attack(float charged_for, int type)
{
	attack_type = type;
	m_charge = charged_for;

	m_state == ItemState::ATTACKING;
}

void MeleeWeapon::use(Character * char_)
{
	player_ignore = char_;
	attacker = char_;

}

void MeleeWeapon::Tick(GameStateData * _GSD)
{

	if (m_state == ItemState::HELD)
	{
		m_pos = player_ignore->GetPos();
	}

	Item::Tick(_GSD);
	if (m_state == ItemState::ATTACKING)
	{
		m_attack_time += _GSD->m_dt;

		Vector2 offset;
		if (attack_type == 1)
		{
			//right
			offset = Vector2(100, 0);
		}
		else if (attack_type == 2)
		{
			//left
			offset = Vector2(-100, 0);
		}
		else if (attack_type == 1)
		{
			//up
			offset = Vector2(0, 100);
		}
		else if (attack_type == 1)
		{
			//down
			offset = Vector2(0, -100);
		}

		m_pos = Vector2::Lerp(attacker->GetPos(), attacker->GetPos() + Vector2(100, 0), m_attack_time);
	}

	if (m_attack_time > 0.5)
	{
		m_pos = attacker->GetPos();
		m_attacking = false;
		m_state = ItemState::HELD;

		if (m_charge > max_charge)
		{
			if (on_full_charge == "tornado")
			{
				//release the tornado
			}
		}
	}

}

void MeleeWeapon::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	if (m_state == ItemState::ATTACKING
		&& _collision->GetOwner()->GetTag() == GameObjectTag::PLAYER
		&& _collision->GetOwner() != player_ignore)
	{
		if (m_charge > max_charge)
		{
			m_charge = max_charge;
		}
		_collision->AddForce(m_charge* Vector2(0, 0));
	}

	Throwable::CollisionEnter(_collision,_normal);
}

void MeleeWeapon::Collision(Physics2D * _collision)
{
}
