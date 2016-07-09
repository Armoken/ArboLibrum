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
	if ((content = loadOrgFile(noteOrg)).empty())
		return NULL;
	string delim = "**";
	vector<string> elems = split(content, delim);

	note = new Note(trim(elems[0].substr(1)), tText);
	for (int i = 1; i < elems.size(); i++)
	{
		note->addNote(trim(elems[i]), tText);
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
