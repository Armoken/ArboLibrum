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

#include "../include/readnote.hpp"

//****************************************************************************

string ReadNote::findFile(string filename)
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

string ReadNote::loadNoteFile(string filename)
{
	string fullPathToFile = ReadNote::findFile(filename);
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

Note* ReadNote::parseNoteFile(string filename)
{
	auto content = ReadNote::loadNoteFile(filename);
	if (content.empty())
	{
		return NULL;
	}

	return NULL;
}
