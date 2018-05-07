#pragma once
#include <string>
#include <fstream>
#include <assert.h>

std::string getFileData(std::ifstream & _file)
{
	int tries = 0;
	char c;
	//look through the file until a '>' is reached
	do
	{
		c = _file.get();
		tries++;
		if (tries > 30)
		{
			return "";
		}
	} while (c != '>');

	//add the rest of the line to the data
	std::string ret_str = "";
	while (true)
	{
		c = _file.get();
		if (c != '\n' && !_file.eof())
		{
			ret_str += c;
		}
		else
		{
			break;
		}
	}

	//return the data
	return ret_str;
}