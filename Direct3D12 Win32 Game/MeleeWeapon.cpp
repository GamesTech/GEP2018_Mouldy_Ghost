#include "pch.h"
#include "MeleeWeapon.h"
#include "Tornado.h"

MeleeWeapon::MeleeWeapon()
{
}

MeleeWeapon::MeleeWeapon(RenderData * _RD, std::string _filename, SpawnHandler * _spawner) : Throwable(_RD, _filename, _spawner)
{
	//need this for instantiiation of the tornado
	m_spawner = _spawner;
	RD_ptr = _RD;
}

MeleeWeapon::MeleeWeapon(Item * item_to_copy, RenderData * _RD, string _filename, SpawnHandler * _spawner) : Throwable(item_to_copy, _RD, _filename, _spawner)
{
	MeleeWeapon* melee_ptr = static_cast<MeleeWeapon*>(item_to_copy);

	max_charge = melee_ptr->getMaxCharge();
	on_full_charge = melee_ptr->getOnFullCharge();
	durability = melee_ptr->getDurability();

	//need this for instantiiation of the tornado
	m_spawner = _spawner;
	RD_ptr = _RD;
}

MeleeWeapon::~MeleeWeapon()
{
}

void MeleeWeapon::attack(float charged_for, int type)
{
	attack_type = type;
	m_charge = charged_for;

	m_attack_time = 0;

	m_state = ItemState::ATTACKING;
}

void MeleeWeapon::use(Character * char_)
{
	player_ignore = char_;
}

void MeleeWeapon::Tick(GameStateData * _GSD)
{
	//type indicates the direction of the attack
	//could be an enum instead of int
	Throwable::Tick(_GSD);

	if (m_state == ItemState::ATTACKING)
	{
		m_attack_time += _GSD->m_dt*3;

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
		else if (attack_type == 3)
		{
			//up
			offset = Vector2(0, -100);
		}
		else if (attack_type == 4)
		{
			//down
			offset = Vector2(0, 100);
		}

		m_pos = Vector2::Lerp(player_ignore->GetPos(), player_ignore->GetPos() + offset, m_attack_time);

		if (m_attack_time > 1)
		{
			
			m_attacking = false;
			m_state = ItemState::HELD;
			player_ignore->setAttacking(false);

			if (m_charge >= max_charge)
			{
				if (on_full_charge == "tornado")
				{
					Tornado* tornado = new Tornado(m_pos, RD_ptr, _GSD, m_spawner, offset);
					m_spawner->onNotify(tornado, Event::OBJECT_INSTANTIATED);
				}
			}
			m_pos = player_ignore->GetPos();
		}
	}

	

}

void MeleeWeapon::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	//hit players only when in attacking state
	if (m_state == ItemState::ATTACKING
		&& _collision->GetOwner()->GetTag() == GameObjectTag::PLAYER
		&& _collision->GetOwner() != player_ignore)
	{
		if (m_charge > max_charge)
		{
			m_charge = max_charge;
		}

		Character* tmpchar = static_cast<Character*>(_collision->GetOwner());	
		Vector2 dir;

		//depending on the attack type
		//knock the target back
		if (attack_type == 1)
		{
			//right
			dir = Vector2((m_power +  m_power * m_charge), -3);
		}
		else if (attack_type == 2)
		{
			//left
			dir = Vector2(-(m_power +  m_power * m_charge),-3);
		}
		else if (attack_type == 3)
		{
			//up
			dir = Vector2(0, -10);
		}
		else if (attack_type == 4)
		{
			//down
			dir = Vector2(0, 10);
		}
		tmpchar->TakeDamage(m_power + m_power*m_charge);
		dir.Normalize();
		tmpchar->Hit(dir, 10000*m_power*m_charge , player_ignore);
	
	}
	else if (m_state == ItemState::THROWN || m_state == ItemState::WAIT ||  m_state == ItemState::SPAWNED)
	{
		Throwable::CollisionEnter(_collision, _normal);
	}
}

void MeleeWeapon::Collision(Physics2D * _collision)
{
}
