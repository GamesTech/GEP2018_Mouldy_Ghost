#include "pch.h"
#include "Characters.h"
#include "RenderData.h"
#include "SpawnHandler.h"
#include "Animation2D.h"

#if _DEBUG
#include "VisiblePhysics.h"
#endif

Character::Character(RenderData* _RD, string _filename)
	: ImageGO2D(_RD, _filename)
{
	CentreOrigin();

	m_damage_emitter = std::make_unique<Emitter>(m_pos, "smoke", _RD);
	m_damage_emitter->setAngle(0);
	m_damage_emitter->setDistribution(3.14159265 *2);
	m_damage_emitter->setSpeeds(200, 300);
	m_damage_emitter->setLifetimes(0.1, 0.5);

	m_die_emitter = std::make_unique<Emitter>(m_pos, "apple", _RD);
	m_die_emitter->setAngle(0);
	m_die_emitter->setDistribution(3.14159265 * 2);
	m_die_emitter->setSpeeds(200, 300);
	m_die_emitter->setLifetimes(1, 3);

	tag = GameObjectTag::PLAYER;
	m_actions = std::make_shared<CharacterActions>();
}

Character::~Character()
{
	m_attacks.clear();
}

void Character::Tick(GameStateData * _GSD)
{
	if (m_lives > 0)
	{
		//get input
		if (m_recovery_time <= 0)
		{
			m_actions->Tick(_GSD, this);
		}
		else
		{
			m_recovery_time -= _GSD->m_dt;
		}

		if (!m_death_zone.Contains(m_pos))
		{
			//DIES
			m_die_emitter->SetPos(m_pos);
			m_die_emitter->addParticles(100);
			if (m_last_to_hit)
			{
				m_last_to_hit->AddPoints(1);
			}
			if (!m_infiniteLives)
			{
				m_lives--;
			}
			m_points--;
			for (int i = 0; i < listeners.size(); i++)
			{
				listeners[i]->onNotify(this, Event::PLAYER_DEAD);
			}
			if (m_lives > 0)
			{
				ResetDamage();
				m_physics->ResetForce(BOTH_AXES);
				ResetPos();
			}
			else
			{
				for (int i = 0; i < listeners.size(); i++)
				{
					listeners[i]->onNotify(this, Event::PLAYER_ELIMINATED);
				}
			}
		}
	}

	//GEP:: Lets go up the inheritence and share our functionality

	//run->update(_GSD);
	m_damage_emitter->SetPos(m_pos);
	m_damage_emitter->Tick(_GSD);
	m_die_emitter->Tick(_GSD);
	m_physics->Tick(_GSD, m_pos);

	//tick buffs
	for (int i = 0; i < buffs.size(); i++)
	{
		if (buffs[i]->Tick(_GSD)) // if returns true, the buff should be deleted
		{
			delete buffs[i];
			buffs.erase(buffs.begin() + i);
			i--;
		}
	}

	GameObject2D::Tick(_GSD);
}

void Character::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
	Rectangle rect;
	rect = Rectangle(0, 0, m_spriteSize.x, m_spriteSize.y);
	
	const RECT* r = &RECT(rect);

	Vector2 render_scale;
	render_scale = m_scale * _zoom;
	Vector2 distance_from_origin = m_pos - _cam_pos;
	distance_from_origin *= _zoom;

	Vector2 render_pos = ((2 * _zoom) * _cam_pos) + distance_from_origin;
	render_pos.x += m_spriteSize.x / 4;

	m_damage_emitter->Render(_RD, 0, _cam_pos, _zoom);
	m_die_emitter->Render(_RD, 0, _cam_pos, _zoom);

	if (m_actions->getUsesAnim)
	{
		m_actions->getActiveAnim()->Render(_RD, _cam_pos, _zoom, render_scale, m_pos, m_resourceNum, m_colour, m_orientation, m_origin, m_actions->isFlipped());
	}
	else
	{
		if (!m_actions->isFlipped())
		{
			_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
				GetTextureSize(allTextures[m_textureIndex].texture.Get()),
				render_pos, r, m_colour, m_orientation, m_origin, render_scale);
		}
		else
		{
			_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
				GetTextureSize(allTextures[m_textureIndex].texture.Get()),
				render_pos, r, m_colour, m_orientation, m_origin, render_scale, SpriteEffects::SpriteEffects_FlipHorizontally, 0);
		}
	}
}

void Character::CreatePhysics(RenderData* _RD)
{
#if _DEBUG
	m_physics = new VisiblePhysics(_RD);
#else
	m_physics = new Physics2D();
#endif

	m_physics->SetBounce(0.3f);
	m_physics->SetGrav(1);
	m_physics->SetOwner(this);
}

void Character::BuffCharacter(Buff * _buff)
{
	buffs.push_back(_buff);
}

void Character::TakeDamage(int _dam)
{
	m_damage += _dam;
	m_damage = m_damage < 0 ? 0 : m_damage;
}

void Character::Hit(Vector2 _dir, float _force, Character* _attacker)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->onNotify(this, Event::PLAYER_HIT);
	}

	//add particles to its emitter
	m_damage_emitter->addParticles(50);

	float knockback = _force * (m_damage + 1) / 100;
	_dir.y += 2;
	m_physics->ResetForce(Axis::BOTH_AXES);
	m_physics->AddForce(_dir * knockback);
	m_recovery_time = 0.1f;
	m_last_to_hit = _attacker;
}

void Character::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	GameObjectTag o_tag = _collision->GetOwner()->GetTag();
	if (o_tag == GameObjectTag::PLATFORM && _normal == Vector2(0,-1))
	{
		m_actions->platformHit();
		m_last_to_hit = nullptr;
	}
}

void Character::CollisionExit(Physics2D * _collision)
{
	GameObjectTag o_tag = _collision->GetOwner()->GetTag();
	if (o_tag == GameObjectTag::PLATFORM)
	{
		m_actions->platformLeave();
	}
}

void Character::Collision(Physics2D * _collision, Vector2 _normal)
{
	GameObjectTag o_tag = _collision->GetOwner()->GetTag();
	if (o_tag == GameObjectTag::PLAYER)
	{
		if (_collision->GetCollider().Center().x > m_pos.x)
		{
			m_pos.x--;
		}
		else
		{
			m_pos.x++;
		}
	}
	if (o_tag == GameObjectTag::PLATFORM && _normal != Vector2(0,-1))
	{
		m_pos.y--;
	}
}

void Character::AddAttack(StandardAttack _attack)
{
	StandardAttack* a = new StandardAttack(_attack);
	m_attacks.push_back(a);
}

void Character::AddAttack(DashAttack _attack)
{
	DashAttack* a = new DashAttack(_attack);
	m_attacks.push_back(a);
}

const Color Character::getTextColour() const
{
	return m_text_colour;
}

void Character::setTextColour(Color colour)
{
	m_text_colour = colour;
}

SpawnHandler * Character::findSpawnHandler()
{
	for (int i = 0; i < listeners.size(); i++)
	{
		SpawnHandler* spawn = nullptr;
		if (spawn = dynamic_cast<SpawnHandler*>(listeners[i]))
		{
			return spawn;
		}
	}
	return nullptr;
}

void Character::setMovement(float speed, int jumps, int height)
{
	m_actions->SetMoveSpeed(speed);
	m_actions->SetJumpLimit(jumps);
	m_actions->SetJumpHeight(height);
}
