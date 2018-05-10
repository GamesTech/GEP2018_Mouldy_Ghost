#pragma once
#include <fstream>
#include <string>
#include <vector>

class CharacterCreator
{
public:
	CharacterCreator() = default;
	~CharacterCreator() = default;

	void create();

private:
	void writeLine(std::ofstream& _character_file, std::string _label, std::string _line);
	
	std::string m_name = "DELETE ME";
	std::string m_image_source = "a";
	float m_move_speed = 0;
	int m_jump_count = 0;
	int m_jump_height = 0;
	std::string m_basic_a = "a";
	std::string m_side_a = "a";
	std::string m_up_a = "a";
	std::string m_down_a = "a";
	std::string m_basic_x = "a";
	std::string m_side_x = "a";
	std::string m_up_x = "a";
	std::string m_down_x = "a";
	std::string m_animations = "a";
};