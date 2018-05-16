#include "pch.h"
#include "AnimationEditorHandler.h"
#include "CharacterManager.h"
#include "AnimationContainer.h"
#include "Animation2D.h"


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
	case Event::ANIMATION_EDITOR_INCREASE_FRAMERATE:
		m_characters[m_selected_char]->getAnimation()->setFramerate
		(m_characters[m_selected_char]->getAnimation()->getFramerate() + 1);
		break;
	case Event::ANIMATION_EDITOR_DECREASE_FRAMERATE:
		m_characters[m_selected_char]->getAnimation()->setFramerate
		(m_characters[m_selected_char]->getAnimation()->getFramerate() - 1);
		break;
	case Event::ANIMATION_EDITOR_DECREASE_FRAMES:
		m_characters[m_selected_char]->getAnimation()->setMaxFrames
		(m_characters[m_selected_char]->getAnimation()->getMaxFrames() - 1);
		break;
	case Event::ANIMATION_EDITOR_INCREASE_FRAMES:
		m_characters[m_selected_char]->getAnimation()->setMaxFrames
		(m_characters[m_selected_char]->getAnimation()->getMaxFrames() + 1);
		break;
	case Event::ANIMATION_EDITOR_INCREASE_X_INCREMENTS:
		m_characters[m_selected_char]->getAnimation()->setIncrements
		(Vector2(m_characters[m_selected_char]->getAnimation()->getIncrements().x + 1,
				m_characters[m_selected_char]->getAnimation()->getIncrements().y));
		break;
	case Event::ANIMATION_EDITOR_DECREASE_X_INCREMENTS:
		m_characters[m_selected_char]->getAnimation()->setIncrements
		(Vector2(m_characters[m_selected_char]->getAnimation()->getIncrements().x - 1,
			m_characters[m_selected_char]->getAnimation()->getIncrements().y));
		break;
	case Event::ANIMATION_EDITOR_DECREASE_Y_INCREMENTS:
		m_characters[m_selected_char]->getAnimation()->setIncrements
		(Vector2(m_characters[m_selected_char]->getAnimation()->getIncrements().x,
			m_characters[m_selected_char]->getAnimation()->getIncrements().y - 1));
		break;
	case Event::ANIMATION_EDITOR_INCREASE_Y_INCREMENTS:
		m_characters[m_selected_char]->getAnimation()->setIncrements
		(Vector2(m_characters[m_selected_char]->getAnimation()->getIncrements().x,
			m_characters[m_selected_char]->getAnimation()->getIncrements().y + 1));
		break;
	case Event::ANIMATION_EDITOR_DECREASE_BOX_WIDTH:
		m_characters[m_selected_char]->getAnimation()->setSpriteBox(
			Rectangle(m_characters[m_selected_char]->getAnimation()->getSpriteBox().x,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().y,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().width - 1,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().height));
		break;
	case Event::ANIMATION_EDITOR_INCREASE_BOX_WIDTH:
		m_characters[m_selected_char]->getAnimation()->setSpriteBox(
			Rectangle(m_characters[m_selected_char]->getAnimation()->getSpriteBox().x,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().y,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().width + 1,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().height));
		break;
	case Event::ANIMATION_EDITOR_DECREASE_BOX_HEIGHT:
		m_characters[m_selected_char]->getAnimation()->setSpriteBox(
			Rectangle(m_characters[m_selected_char]->getAnimation()->getSpriteBox().x,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().y,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().width,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().height - 1));
		break;
	case Event::ANIMATION_EDITOR_INCREASE_BOX_HEIGHT:
		m_characters[m_selected_char]->getAnimation()->setSpriteBox(
			Rectangle(m_characters[m_selected_char]->getAnimation()->getSpriteBox().x,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().y,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().width,
				m_characters[m_selected_char]->getAnimation()->getSpriteBox().height + 1));
		break;
	case Event::ANIMATION_EDITOR_DECREASE_FURTHEST_LEFT:
		m_characters[m_selected_char]->getAnimation()->setFurthestLeftPos(
			m_characters[m_selected_char]->getAnimation()->getFurthestLeftPos() - 1);
		break;
	case Event::ANIMATION_EDITOR_INCREASE_FURTHEST_LEFT:
		m_characters[m_selected_char]->getAnimation()->setFurthestLeftPos(
			m_characters[m_selected_char]->getAnimation()->getFurthestLeftPos() + 1);
		break;
	case Event::ANIMATION_EDITOR_DECREASE_START_X:
		m_characters[m_selected_char]->getAnimation()->setSpriteBoxStartPos(
		Vector2(m_characters[m_selected_char]->getAnimation()->getSpriteboxStartPos().x -1,
			m_characters[m_selected_char]->getAnimation()->getSpriteboxStartPos().y));
		break;
	case Event::ANIMATION_EDITOR_INCREASE_START_X:
		m_characters[m_selected_char]->getAnimation()->setSpriteBoxStartPos(
			Vector2(m_characters[m_selected_char]->getAnimation()->getSpriteboxStartPos().x + 1,
				m_characters[m_selected_char]->getAnimation()->getSpriteboxStartPos().y));
		break;
	case Event::ANIMATION_EDITOR_DECREASE_START_Y:
		m_characters[m_selected_char]->getAnimation()->setSpriteBoxStartPos(
			Vector2(m_characters[m_selected_char]->getAnimation()->getSpriteboxStartPos().x,
				m_characters[m_selected_char]->getAnimation()->getSpriteboxStartPos().y - 1));
		break;
	case::Event::ANIMATION_EDITOR_INCREASE_START_Y:
		m_characters[m_selected_char]->getAnimation()->setSpriteBoxStartPos(
			Vector2(m_characters[m_selected_char]->getAnimation()->getSpriteboxStartPos().x,
				m_characters[m_selected_char]->getAnimation()->getSpriteboxStartPos().y + 1));
		break;
	case::Event::ANIMATION_EDITOR_SAVE_DATA:
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
