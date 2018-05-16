#pragma once
#include "EventHandler.h"
#include "Characters.h"

class CharacterManager;
class AnimationContainer;

class AnimationEditorHandler :
	public EventHandler
{
public:
	AnimationEditorHandler();
	~AnimationEditorHandler();

	std::string getType() override { return "AnimationEditor"; };

	void onNotify(GameObject2D* entity_, Event event_) override;

	void tieCharacterManager(CharacterManager* _manager);

	Character getSelectedChar();
	int getSelectedCharIndex() { return m_selected_char; };

	void addAnimationContainer(AnimationContainer* _character);

private:
	int m_selected_char = 0;
	std::vector<AnimationContainer*> m_characters;
	CharacterManager* m_character_manager;
};

