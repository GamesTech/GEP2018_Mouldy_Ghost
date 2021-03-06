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
		assert(tries < 10000);	//breaks here if it gets stuck in the file
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

//If the file is definitely correct, check if there is not an extra space or extra line at the end 