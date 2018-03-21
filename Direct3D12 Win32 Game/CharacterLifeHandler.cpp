#include "pch.h"
#include "CharacterLifeHandler.h"
#include "GameOverScene.h"

void CharacterLifeHandler::onNotify(GameObject2D * entity_, Event event_)
{
	Character* c = static_cast<Character*>(entity_);
	if (c)
	{
		switch (event_)
		{
		case PLAYER_ELIMINATED:
			m_go_scene->PlayerEliminated(c, c->GetControllerIndex());
			break;
		case PLAYER_SPAWN:
			m_go_scene->AddCharacterToScene(c);
			break;
		}
	}
}