/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

#include "../include/readorg.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

//****************************************************************************************************

Note* ReadOrg::readNote(string noteOrg)
{
	Note* note;
	string content;
	string level = "**";
	if ((content = loadOrgFile(noteOrg)).empty())
		return NULL;

	note = read(content, level, tRoot);
	note->setPath(note->getText() + ".org");

	return note;
}

Note* ReadOrg::read(string nodeContent, string level, NoteTypes type)
{
	string delim = level;
	vector<string> elems = split(nodeContent, delim);
	int index = 0, size = elems.size();

	while (index < size)
	{
		if (elems[index] == "")
		{
			elems[index] += delim + elems[index + 1];
			for (int j = index + 1; j < size - 1; j++)
			{
				elems[j] = elems[j + 1];
			}
			elems[size - 1].erase();
			size--;
		}
		index++;
	}

	Note *note = new Note(trim(elems[0].substr(delim.length())), type);
	Note* newNote;

	for (int i = 1; i < elems.size(); i++)
	{
		if (!elems[i].empty())
		{
			if (elems[i][0] == '*')
			{
				Note* innerNote = read(elems[i], delim, tText);
				newNote->addNote(innerNote);
			}
			else
			{
				newNote = new Note(trim(elems[i]), tText);
				note->addNote(newNote);
			}
		}
	}

	return note;
}

//****************************************************************************************************

string ReadOrg::loadOrgFile(string filename)
{
	filename = "./Org/" + filename + ".org";

	ifstream in(filename);
	string content;

	if (!in.is_open())
	{
		cout << "Such note does not exists!" << endl;
		return string();
	}

	copy(istreambuf_iterator<char>(in), istreambuf_iterator<char>(), back_inserter(content));
	in.close();

	return content;
}

//****************************************************************************************************

vector<string> ReadOrg::split(const string& s, const string& delim, const bool keep_empty)
{
	vector<string> result;
	if (delim.empty()) {
		result.push_back(s);
		return result;
	}
	string::const_iterator substart = s.begin(), subend;
	while (true) {
		subend = search(substart, s.end(), delim.begin(), delim.end());
		string temp(substart, subend);
		if (keep_empty || !temp.empty()) {
			result.push_back(temp);
		}
		if (subend == s.end()) {
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}

//****************************************************************************************************

string ReadOrg::trim(string &str)
{
	size_t endpos = str.find_last_not_of(" \t\n");
	if (string::npos != endpos)
	{
		str = str.substr(0, endpos + 1);
	}

	size_t startpos = str.find_first_not_of(" \t\n");
	if (string::npos != startpos)
	{
		str = str.substr(startpos);
	}

	return str;
}

//****************************************************************************************************
