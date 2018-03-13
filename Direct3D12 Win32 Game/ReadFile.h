#pragma once
#include <string>
#include <fstream>
#include <assert.h>

std::string getFileData(std::ifstream & _file)
{
	int tries = 0;
	char c;
	do
	{
		c = _file.get();
		tries++;
		assert(tries < 10000);	//breaks here if it gets stuck in the file
	} while (c != '>');

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

	return ret_str;
}