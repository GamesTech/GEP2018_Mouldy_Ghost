#pragma once
#include <vector>

class Character;
class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager() = default;

	Character* GetCharacterByName(std::string _name);
	void PopulateCharacterList(RenderData* _RD);
private:
	std::vector<Character*> m_character_list;
};