#include "pch.h"
#include "CharacterCreator.h"

void CharacterCreator::create()
{
	std::ofstream character_file;
	character_file.open("../../GameAssets/Characters/" + m_name + ".txt", std::fstream::out);
	writeLine(character_file, "Image", m_image_source);
	writeLine(character_file, "Speed", std::to_string(m_move_speed));
	writeLine(character_file, "Jump Count", std::to_string(m_jump_count));
	writeLine(character_file, "Jump Height", std::to_string(m_jump_height));
	writeLine(character_file, "A", m_basic_a);
	writeLine(character_file, "Side + A", m_side_a);
	writeLine(character_file, "Up + A", m_up_a);
	writeLine(character_file, "Down + A", m_down_a);
	writeLine(character_file, "X", m_basic_x);
	writeLine(character_file, "Side + X", m_side_x);
	writeLine(character_file, "Up + X", m_up_x);
	writeLine(character_file, "Down + X", m_down_x);
	writeLine(character_file, "Animations", m_animations);

	character_file.close();

	std::ofstream all_char_file;
	all_char_file.open("../../GameAssets/Characters/AllCharacters.txt", std::fstream::out | std::fstream::app);
	writeLine(all_char_file, "", m_name);
	all_char_file.close();
}

void CharacterCreator::writeLine(std::ofstream & _character_file, std::string _label, std::string _line)
{
	for (char c : _label)
	{
		_character_file << c;
	}
	_character_file << '>';
	for (char c : _line)
	{
		_character_file << c;
	}
	_character_file << '\n';
}