#include "pch.h"
#include "AnimationEditorHandler.h"
#include "CharacterManager.h"
#include "AnimationContainer.h"


AnimationEditorHandler::AnimationEditorHandler()
{
}


AnimationEditorHandler::~AnimationEditorHandler()
{
}

void AnimationEditorHandler::onNotify(GameObject2D * entity_, Event event_)
{
	switch (event_)
	{
	case Event::CHANGE_SCENE_ANIMATION_EDITOR:
		break;
	case Event::ANIMATION_EDITOR_NEXT_CHARACTER:
		if (m_selected_char < m_character_manager->GetCharCount() - 1)
		{
			m_selected_char++;
		}
		else
		{
			m_selected_char = 0;
		}
		break;
	case Event::ANIMATION_EDITOR_PREV_CHARACTER:
		if (m_selected_char <= 0)
		{
			m_selected_char = m_character_manager->GetCharCount() - 1;
		}
		else
		{
			m_selected_char--;
		}
		break;
	case Event::ANIMATION_EDITOR_NEXT_ANIM:
		m_characters[m_selected_char]->changeAnimation(1);
		break;
	case Event::ANIMATION_EDITOR_PREV_ANIM:
		m_characters[m_selected_char]->changeAnimation(-1);
		break;
	}
}

void AnimationEditorHandler::tieCharacterManager(CharacterManager * _manager)
{
	m_character_manager = _manager;
}

Character AnimationEditorHandler::getSelectedChar()
{
	return m_character_manager->GetCharacter(m_selected_char);
}

void AnimationEditorHandler::addAnimationContainer(AnimationContainer * _character)
{
	m_characters.push_back(_character);
}
