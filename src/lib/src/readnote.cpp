/*****************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████

(c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************/

#include "../include/serialization.hpp"

//****************************************************************************

string Serializer::findFile(string filename)
{
	if (ifstream(filename))
	{
		return filename;
	}
	else if (ifstream("./Note/" + filename))
	{
		return "./Note/" + filename;
	}
	else
	{
		return string();
	}
}

string Serializer::loadNoteFile(string filename)
{
	string fullPathToFile = Serializer::findFile(filename);
	if (fullPathToFile.empty())
	{
		cout << "Such note does not exists!" << endl;
		return string();
	}

	ifstream inputFile(fullPathToFile);
	stringstream strStream;
	strStream << inputFile.rdbuf();
	return strStream.str();
}

Note* Serializer::parseNoteFile(string filename)
{
	auto content = Serializer::loadNoteFile(filename);
	if (content.empty())
	{
		return NULL;
	}

	return NULL;
}
