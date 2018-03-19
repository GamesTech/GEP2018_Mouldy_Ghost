#pragma once
#include <vector>

class Character;
class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager() = default;

	const int GetCharCount() { return m_character_list.size(); }
	Character GetCharacter(std::string _name);
	Character GetCharacter(int _index);
	void PopulateCharacterList(RenderData* _RD, SpawnHandler* _spawner);
private:
	std::vector<Character> m_character_list;
};