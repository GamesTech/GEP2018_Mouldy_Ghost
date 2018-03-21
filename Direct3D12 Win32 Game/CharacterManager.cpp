#include "pch.h"
#include "CharacterManager.h"
#include "ReadFile.h"
#include "StandardAttack.h"
#include "DashAttack.h"

CharacterManager::CharacterManager()
{
	m_character_list.reserve(20);
}

Character CharacterManager::GetCharacter(std::string _name)
{
	for (int i = 0; i < m_character_list.size(); i++)
	{
		if (m_character_list[i].GetName() == _name)
		{
			return m_character_list[i];
		}
	}
	assert(false);
}

Character CharacterManager::GetCharacter(int _index)
{
	return m_character_list[_index];
}

void CharacterManager::PopulateCharacterList(RenderData* _RD)
{
	std::ifstream all_characters_file;
	all_characters_file.open("..\\GameAssets\\Characters\\AllCharacters.txt");
	while (!all_characters_file.eof())
	{
		std::string char_name = getFileData(all_characters_file);

		std::ifstream character_file;
		character_file.open("..\\GameAssets\\Characters\\" + char_name + ".txt");

		std::string imageFile = getFileData(character_file);
		Character character = Character(_RD, imageFile);
		character.SetName(char_name);

		float speed = std::stof(getFileData(character_file));
		character.SetMoveSpeed(speed);
		int jump_limit = std::stoi(getFileData(character_file));
		character.SetJumpLimit(jump_limit);
		int jump = std::stoi(getFileData(character_file));
		character.SetJumpHeight(jump);

		while(!character_file.eof())
		{
			std::string attack_file = getFileData(character_file);
			switch (attack_file[0])
			{
			case 'M':
			case 'R':
				character.AddAttack(StandardAttack(attack_file, _RD));
				break;
			case 'D':
				character.AddAttack(DashAttack(attack_file, _RD));
				break;
			default:
				break;
			}
		}
		character_file.close();

		m_character_list.push_back(character);
	}
	all_characters_file.close();
}