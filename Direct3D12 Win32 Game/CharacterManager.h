#pragma once
#include <vector>

/*
This is the class which hold and deals with the game's characters
*/

class Character;
class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager() = default;

	const int GetCharCount() { return m_character_list.size(); }
	//finds character by name
	Character GetCharacter(std::string _name);
	//finds character by index
	Character GetCharacter(int _index);
	//gets all characters from appropriate file
	void PopulateCharacterList(RenderData* _RD);
private:
	std::vector<Character> m_character_list;
};